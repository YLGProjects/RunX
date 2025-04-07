/**
 * MIT License
 *
 * Copyright (c) 2024 ylgeeker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "core/application/service_registry.h"
#include "core/assist/macro.h"
#include "core/assist/math.h"
#include "core/assist/time.h"
#include "core/error/error.h"
#include "core/log/log.h"

#include <etcd/Client.hpp>
#include <etcd/KeepAlive.hpp>

#include <exception>
#include <memory>
#include <string>

namespace ylg {
namespace app {

ServiceRegistry::ServiceRegistry(const std::string& serviceName, const std::string& etcdURLs,
                                 const std::string& user, const std::string& password, int ttl)
{
    _serviceName = serviceName;
    _etcdURLs    = etcdURLs;
    _user        = user;
    _password    = password;
    _instanceID  = assist::UUID();

    if (ttl < YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT)
    {
        ttl = YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT;
    }

    _ttl = ttl;
}

EtcdClientPtr ServiceRegistry::EtcdClient()
{
    return _client;
}

std::error_code ServiceRegistry::Run()
{
    if (_client == nullptr)
    {
        CreateEtcdClient();
    }

    auto ec = DoRegister(_serviceName, _instanceID, YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT);
    if (!ylg::error::IsSuccess(ec))
    {
        LOG_WARN("can not register service. name:{}", _serviceName);
        return ec;
    }

    _keepRunning        = true;
    _checkHealthyThread = std::thread([this]() {
        while (_keepRunning)
        {
            CheckHealthy(_serviceName, _instanceID);
            assist::MilliSleep(50);
        }
    });

    return ylg::error::ErrorCode::SUCCESS;
}

void ServiceRegistry::Close()
{
    _keepRunning = false;

    if (_keepalive)
    {
        _keepalive->Cancel();
    }

    if (_checkHealthyThread.joinable())
    {
        _checkHealthyThread.join();
    }

    _client->rm(_serviceName).wait();
}

void ServiceRegistry::CreateEtcdClient()
{
    if (_client == nullptr)
    {
        _client = std::make_shared<etcd::Client>(_etcdURLs, _user, _password);
    }
}

std::error_code ServiceRegistry::DoRegister(const std::string& key, const std::string& value, int retryMax)
{
    if (retryMax < YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT)
    {
        retryMax = YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT;
    }

    etcd::Response resp = _client->leasegrant(_ttl).get();
    if (!resp.is_ok())
    {
        LOG_WARN("service registry, lease grant failed. key:{}, errmsg:{}", key, resp.error_message());
        return ylg::error::ErrorCode::DISCOVERY_CREATE_LEASE_FAILURE;
    }

    _leaseID   = resp.value().lease();
    _keepalive = std::make_shared<etcd::KeepAlive>(*_client, _ttl, _leaseID);

    while (--retryMax > 0)
    {
        auto resp = _client->set(key, value, _leaseID).get();
        if (!resp.is_ok())
        {
            assist::MilliSleep(50);
            continue;
        }

        return ylg::error::ErrorCode::SUCCESS;
    }

    return ylg::error::ErrorCode::DISCOVERY_REGISTER_SERVICE_FAILURE;
}

void ServiceRegistry::CheckHealthy(const std::string& key, const std::string& value)
{
    BEGIN_TRY

    _keepalive->Check();

    END_TRY_BEGIN_CATCH(std::exception, e)

    LOG_WARN("service registry, keepalive is invalid, renew one. key:{}, ttl:{}, errmsg:{}", key, _ttl, e.what());

    _keepalive = std::make_shared<etcd::KeepAlive>(*_client, _ttl, _leaseID);

    END_CATCH

    if (CheckRegistrationActive(key, value))
    {
        return;
    }

    LOG_DEBUG("register service. name:{}", key);

    auto ec = DoRegister(key, value, YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT);
    if (!ylg::error::IsSuccess(ec))
    {
        LOG_WARN("can not register service. name:{}", key);
    }
}

bool ServiceRegistry::CheckRegistrationActive(const std::string& key, const std::string& endpoint)
{
    static uint64_t lastCheck  = 0;
    bool            lastResult = true;

    auto now = assist::TimestampTickCountSecond();
    if (now - lastCheck < 5)
    {
        return lastResult;
    }

    BEGIN_TRY

    etcd::Response keyResp   = _client->get(key).get();
    etcd::Response leaseResp = _client->leasetimetolive(_leaseID).get();

    bool keyOk   = keyResp.is_ok() && (keyResp.value().as_string() == endpoint);
    bool leaseOk = leaseResp.is_ok() && (leaseResp.value().ttl() > 0);

    lastResult = keyOk && leaseOk;
    lastCheck  = now;

    LOG_DEBUG("check registration result. key:{}, value:{}, endpoint:{}, result:{}", key, keyResp.value().as_string(), endpoint, lastResult);

    END_TRY
    BEGIN_CATCH(std::exception, e)

    LOG_WARN("check registration failed. key:{}, endpoint:{}, errmsg:{}", key, endpoint, e.what());
    lastResult = false;

    END_CATCH

    return lastResult;
}

} // namespace app
} // namespace ylg
