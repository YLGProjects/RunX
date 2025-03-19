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

#ifndef _YLG_CORE_NET_TCP_CLIENT_H_
#define _YLG_CORE_NET_TCP_CLIENT_H_

#include "core/net/message.h"
#include "core/net/tcp_connection.h"
#include "core/net/tcp_handler.h"

#include <event2/bufferevent.h>
#include <event2/event.h>

#include <cstdint>
#include <future>
#include <memory>
#include <system_error>

namespace ylg {
namespace net {

class TCPClient final
{
public:
    TCPClient();
    ~TCPClient();

public:
    static void ReadCallback(bufferevent* bev, void* ctx);
    static void EventCallback(bufferevent* bev, short events, void* ctx);
    static void CheckConnectionState(evutil_socket_t fd, short events, void* ctx);
    static void ConnectionKeepalive(evutil_socket_t fd, short events, void* ctx);

public:
    void            SetTimeout(int timeoutSec);
    void            SetCallback(TCPHandlerCallbackFunctor functor);
    std::error_code Connect(const std::string& ip, uint16_t port);
    void            Close();
    std::error_code Send(const Message& msg);

private:
    void            Run();
    std::error_code Reconnect();
    bool            ProcessCoreMessage(TCPConnectionPtr conn, MessagePtr msg);

private:
    timeval                   _checkConnectionTimeoutSeconds     = {YLG_NET_TCP_CONNECTION_TIMEOUT_SECOND_DFT, 0};
    timeval                   _connectionKeepaliveTimeoutSeconds = {YLG_NET_TCP_CONNECTION_KEEPALIVE_TIMEOUT_SECOND_DFT, 0};
    TCPHandlerCallbackFunctor _functor                           = nullptr;
    std::string               _remoteIP;
    uint16_t                  _remotePort = 0;
    std::future<void>         _asyncRun;
    TCPConnectionPtr          _connection                = nullptr;
    event*                    _checkConnectionStateEvent = nullptr;
    event*                    _connectionKeepaliveEvent  = nullptr;
    event_base*               _base                      = nullptr;
    bufferevent*              _bev                       = nullptr;
};

using TCPClientPtr = std::shared_ptr<TCPClient>;

} // namespace net
} // namespace ylg
#endif

