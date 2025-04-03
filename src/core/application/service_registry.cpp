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
#include <string>

namespace ylg {
namespace app {

ServiceRegistry::ServiceRegistry(const std::string& serviceName, const std::string& etcdURL,
                                 const std::string& user, const std::string& password, int ttl)
{
    _serviceName = serviceName;
    _etcdURL     = etcdURL;
    _user        = user;
    _password    = password;
    _instanceID  = assist::UUID();

    if (ttl < YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT)
    {
        _ttl = ttl;
    }
}

ETCDClientPtr ServiceRegistry::GetClient()
{
    return _client;
}

std::error_code ServiceRegistry::Run()
{
    if (_client == nullptr)
    {
        CreateEtcdClient();
    }

    auto ec = DoRegister(_serviceName, _instanceID, _ttl, YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT);
    if (!ylg::error::IsSuccess(ec))
    {
        LOG_WARN("can not register service. name:{}", _serviceName);
        return ec;
    }

    _keepaliveThread = std::thread([this]() {
        while (_keepRunning)
        {
            _client->leasekeepalive(_leaseID).get();
            assist::Sleep(_ttl / 2);
        }
    });

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

    if (_keepaliveThread.joinable())
    {
        _keepaliveThread.join();
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
        _client = std::make_shared<etcd::Client>(_etcdURL, _user, _password);
    }
}

std::error_code ServiceRegistry::DoRegister(const std::string& key, const std::string& value,
                                            int ttl, int retryMax)
{
    if (ttl < YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT)
    {
        ttl = YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT;
    }

    if (retryMax < YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT)
    {
        retryMax = YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT;
    }

    etcd::Response resp = _client->leasegrant(ttl).get();
    if (!resp.is_ok())
    {
        return ylg::error::ErrorCode::DISCOVERY_CREATE_LEASE_FAILURE;
    }

    _leaseID = resp.value().lease();

    while (--retryMax > 0)
    {
        resp = _client->set(key, value, _leaseID).get();
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
    if (CheckRegistrationActive(key, value))
    {
        return;
    }

    LOG_DEBUG("register service. name:{}", key);

    auto ec = DoRegister(key, value, _ttl, YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT);
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

    END_TRY
    BEGIN_CATCH(std::exception, e)

    lastResult = false;

    END_CATCH

    return lastResult;
}

} // namespace app
} // namespace ylg
