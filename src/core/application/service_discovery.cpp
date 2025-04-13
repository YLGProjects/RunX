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
#include "core/log/log.h"

#include <etcd/Response.hpp>
#include <etcd/Watcher.hpp>

namespace ylg {
namespace app {

ServiceDiscovery::ServiceDiscovery(const std::string& etcdURLs, const std::string& user, const std::string& password)
{
    _etcdURLs = etcdURLs;
    _user     = user;
    _password = password;
}

ServiceDiscovery::ServiceDiscovery(std::shared_ptr<etcd::Client> etcdClient)
{
    _client = etcdClient;
}

ServiceDiscovery::~ServiceDiscovery()
{
    _watcherHandlers.Foreach([](const std::string& key, WatcherHandlerPtr handler) {
        handler->_watcher->Cancel();
    });

    _watcherHandlers.Clean();
}

std::error_code ServiceDiscovery::List(const std::string& key, std::vector<std::string>& values)
{
    if (_client == nullptr)
    {
        CreateEtcdClient();
    }

    etcd::Response resp = _client->ls(key).get();

    std::vector<std::string> endpoints;
    if (!resp.is_ok())
    {
        LOG_WARN("failed to list the key:{}, errmsg:{}", key, resp.error_message());
        return ylg::error::ErrorCode::ERROR;
    }

    for (const auto& kv : resp.values())
    {
        endpoints.push_back(kv.as_string());
    }

    return ylg::error::ErrorCode::SUCCESS;
}

std::error_code ServiceDiscovery::OpenWatcher(const std::string& key, EventHandler handler, bool recursive)
{
    if (_client == nullptr)
    {
        CreateEtcdClient();
    }

    if (_watcherHandlers.Exists(key))
    {
        LOG_WARN("service discovery, rewatched. key:{}, watcher size:{}", key, _watcherHandlers.Count());
        return ylg::error::ErrorCode::DISCOVERY_WATCHER_REPEATED;
    }

    auto watcherHandler        = std::make_shared<WatcherHandler>();
    watcherHandler->_handler   = handler;
    watcherHandler->_recursive = recursive;

    auto watcher = std::make_shared<etcd::Watcher>(*_client,
                                                   key,
                                                   std::bind(&ServiceDiscovery::HandleWatchResponse,
                                                             this, std::placeholders::_1),
                                                   recursive);

    watcher->Wait([=, this](bool cancelled) {
        if (!cancelled)
        {
            // reset watcher
            auto watcher             = std::make_shared<etcd::Watcher>(*_client,
                                                                       key,
                                                                       std::bind(&ServiceDiscovery::HandleWatchResponse,
                                                                                 this, std::placeholders::_1),
                                                                       recursive);
            watcherHandler->_watcher = watcher;
            _watcherHandlers.Push(key, watcherHandler);
        }
    });

    watcherHandler->_watcher = watcher;
    _watcherHandlers.Push(key, watcherHandler);

    return ylg::error::ErrorCode::SUCCESS;
}

void ServiceDiscovery::CloseWatcher(const std::string& key)
{
    auto watcherHandler = _watcherHandlers.Remove(key);

    if (watcherHandler == nullptr)
    {
        return;
    }

    watcherHandler->_watcher->Cancel();
}

void ServiceDiscovery::CreateEtcdClient()
{
    if (_client == nullptr)
    {
        _client = std::make_shared<etcd::Client>(_etcdURLs, _user, _password);
    }
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
        std::string key, value;
        EventType   type = EventType::UNKNOWN;

        switch (event.event_type())
        {
        case etcd::Event::EventType::PUT:
            key   = event.kv().key();
            value = event.kv().as_string();
            type  = EventType::PUT;

            LOG_DEBUG("service discovery watcher put response. key:{}, value:{}", key, value);
            break;

        case etcd::Event::EventType::DELETE_:
            key   = event.kv().key();
            value = event.kv().as_string();
            type  = EventType::DELETE;

            LOG_DEBUG("service discovery watcher delete response. key:{}, value:{}", event.kv().key(), event.kv().as_string());
            break;
        default:
            LOG_DEBUG("service discovery watcher invalid response. key:{}, value:{}", event.kv().key(), event.kv().as_string());
            break;
        }

        if (type == EventType::UNKNOWN)
        {
            continue;
        }

        _watcherHandlers.Foreach([&](const std::string& eleKey, WatcherHandlerPtr handler) {
            if (eleKey.size() > key.size())
            {
                // eleKey is child, skip
                return;
            }

            if (handler->_recursive)
            {
                if (key.find(eleKey) != std::string::npos)
                {
                    handler->_handler(key, value, type);
                }

                return;
            }

            if (key == eleKey)
            {
                handler->_handler(key, value, type);
            }
        });
    }
}

} // namespace app
} // namespace ylg

