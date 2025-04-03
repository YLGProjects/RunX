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

#include "core/application/service_discovery.h"
#include "core/error/error.h"

#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>

namespace ylg {
namespace app {

ServiceDiscovery::ServiceDiscovery(const std::string& etcdURL, const std::string& user, const std::string& password)
    : _client(etcdURL, user, password) {}

ServiceDiscovery::~ServiceDiscovery()
{
    _watchers.Foreach([](std::string key, std::shared_ptr<etcd::Watcher> value) {
        value->Cancel();
    });

    _watchers.Clean();
}

std::vector<std::string> ServiceDiscovery::Discover(const std::string& key)
{
    etcd::Response resp = _client.ls(key).get();

    std::vector<std::string> endpoints;
    if (resp.is_ok())
    {
        for (const auto& kv : resp.values())
        {
            endpoints.push_back(kv.as_string());
        }
    }

    return endpoints;
}

std::error_code ServiceDiscovery::OpenWatcher(const std::string& key)
{
    if (!_watchers.Exists(key))
    {
        return ylg::error::ErrorCode::DISCOVERY_WATCHER_REPEATED;
    }

    auto watcher = std::make_shared<etcd::Watcher>(_client, key,
                                                   std::bind(&ServiceDiscovery::HandleWatchResponse, this, std::placeholders::_1),
                                                   true);

    watcher->Wait([=, this](bool cancelled) {
        if (!cancelled)
        {
            // reset watcher
            auto watcher = std::make_shared<etcd::Watcher>(_client, key,
                                                           std::bind(&ServiceDiscovery::HandleWatchResponse, this, std::placeholders::_1),
                                                           true);
            _watchers.Push(key, watcher);
        }
    });

    _watchers.Push(key, watcher);

    return ylg::error::ErrorCode::SUCCESS;
}

void ServiceDiscovery::CloseWatcher(const std::string& key)
{
    auto watcher = _watchers.Remove(key);
    if (watcher == nullptr)
    {
        return;
    }

    watcher->Cancel();
}

void ServiceDiscovery::HandleWatchResponse(etcd::Response response)
{
    if (response.error_code())
    {
        LOG_WARN("service discovery watcher. errmsg:{}", response.error_message());
        return;
    }

    for (const auto& event : response.events())
    {
        switch (event.event_type())
        {
        case etcd::Event::EventType::PUT:
            LOG_DEBUG("service discovery watcher put response. key:{}, value:{}", event.kv().key(), event.kv().as_string());
            break;

        case etcd::Event::EventType::DELETE_:
            LOG_DEBUG("service discovery watcher delete response. key:{}, value:{}", event.kv().key(), event.kv().as_string());
            break;
        default:
            LOG_DEBUG("service discovery watcher invalid response. key:{}, value:{}", event.kv().key(), event.kv().as_string());
            break;
        }
    }
}

} // namespace app
} // namespace ylg
