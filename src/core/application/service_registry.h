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

#ifndef _YLG_CORE_APP_SERVICE_REGISTRY_H_
#define _YLG_CORE_APP_SERVICE_REGISTRY_H_

#include "core/error/error.h"

#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>

#include <atomic>
#include <memory>
#include <string>
#include <system_error>

// clang-format off

#define YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT       30
#define YLG_CORE_APP_SERVICE_REGISTRY_RETRY_MAX_DFT 3

// clang-format on

namespace ylg {
namespace app {

using EtcdClientPtr = std::shared_ptr<etcd::Client>;
using RootKeyValue  = std::atomic<std::shared_ptr<std::string>>;

class ServiceRegistry final
{
public:
    ServiceRegistry(const std::string& serviceName, const std::string& etcdURLs,
                    const std::string& user, const std::string& password, int ttl = 0);

    ~ServiceRegistry() = default;

public:
    EtcdClientPtr   EtcdClient();
    std::error_code Run(const std::string& rootKeyValue);
    std::error_code Set(const std::string& key, const std::string& value, int retryMax = 0);
    std::string     GetID();
    std::string     GetRootKey();
    void            Close();

private:
    void            CreateEtcdClient();
    std::error_code DoRegister(const std::string& key, const std::string& value, int retryMax = 0);
    void            CheckHealthy(const std::string& key, const std::string& value);
    bool            CheckRegistrationActive(const std::string& key, const std::string& endpoint);

private:
    // eg: http://127.0.0.1:2379;http://127.0.0.1:2379
    std::string                      _etcdURLs;
    std::string                      _user;
    std::string                      _password;
    std::string                      _serviceName;
    std::string                      _instanceID;
    std::string                      _rootKey;
    RootKeyValue                     _rootKeyValue;
    std::shared_ptr<etcd::Client>    _client;
    int                              _ttl     = YLG_CORE_APP_SERVICE_REGISTRY_TTL_DFT;
    int64_t                          _leaseID = 0;
    std::shared_ptr<etcd::KeepAlive> _keepalive;
    std::thread                      _checkHealthyThread;
    std::atomic_bool                 _keepRunning = true;
};

using ServiceRegistryPtr = std::shared_ptr<ServiceRegistry>;

} // namespace app
} // namespace ylg

#endif

