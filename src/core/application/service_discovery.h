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

class ServiceDiscovery
{
public:
    ServiceDiscovery(const std::string& etcdURL, const std::string& user, const std::string& password);
    ~ServiceDiscovery();

public:
    std::vector<std::string> Discover(const std::string& serviceName);
    std::error_code          OpenWatcher(const std::string& key);
    void                     CloseWatcher(const std::string& key);

private:
    void HandleWatchResponse(etcd::Response response);

private:
    etcd::Client _client;
    // Key: service name, Value: watcher
    container::SafeMap<std::string, std::shared_ptr<etcd::Watcher>> _watchers;
};

using ServiceDiscoveryPtr = std::shared_ptr<ServiceDiscovery>;

} // namespace app
} // namespace ylg

#endif

