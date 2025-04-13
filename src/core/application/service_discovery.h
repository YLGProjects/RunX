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

#ifndef _YLG_CORE_APP_SERVICE_DISCOVERY_H_
#define _YLG_CORE_APP_SERVICE_DISCOVERY_H_

#include "core/container/safe_map.h"
#include "core/error/error.h"

#include <etcd/Client.hpp>
#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>

#include <memory>
#include <string>
#include <vector>

namespace ylg {
namespace app {

enum class EventType : int32_t
{
    PUT,
    DELETE,
    UNKNOWN,
};

using EventHandler = std::function<void(const std::string& key, const std::string& value, EventType type)>;

struct WatcherHandler
{
    std::string                    _key;
    EventHandler                   _handler;
    bool                           _recursive = true;
    std::shared_ptr<etcd::Watcher> _watcher;
};

using WatcherHandlerPtr = std::shared_ptr<WatcherHandler>;

class ServiceDiscovery
{
public:
    ServiceDiscovery(const std::string& etcdURLs, const std::string& user, const std::string& password);
    ServiceDiscovery(std::shared_ptr<etcd::Client> etcdClient);
    ~ServiceDiscovery();

public:
    std::error_code List(const std::string& key, std::vector<std::string>& values);
    std::error_code OpenWatcher(const std::string& key, EventHandler handler, bool recursive = true);
    void            CloseWatcher(const std::string& key);

private:
    void CreateEtcdClient();
    void HandleWatchResponse(etcd::Response response);

private:
    // eg: http://127.0.0.1:2379;http://127.0.0.1:2379
    std::string                   _etcdURLs;
    std::string                   _user;
    std::string                   _password;
    std::shared_ptr<etcd::Client> _client;

    // Key: service name, Value: watcher
    container::SafeMap<std::string, WatcherHandlerPtr> _watcherHandlers;
};

using ServiceDiscoveryPtr = std::shared_ptr<ServiceDiscovery>;

} // namespace app
} // namespace ylg

#endif

