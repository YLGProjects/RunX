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

#ifndef _YLG_CORE_NET_TCP_SERVER_H_
#define _YLG_CORE_NET_TCP_SERVER_H_

#include "core/net/tcp_connection.h"
#include "core/net/tcp_handler.h"

#include <event2/listener.h>

#include <atomic>
#include <cstdint>
#include <event2/util.h>
#include <memory>
#include <vector>

namespace ylg {
namespace net {

class TCPServer final
{
public:
    TCPServer(const std::string& listenAddress, uint16_t port, int threadCount = 3);
    ~TCPServer();

public:
    static void AcceptCallback(struct evconnlistener* listener, evutil_socket_t fd,
                               sockaddr* address, int socklen, void* ctx);

public:
    void            SetTimeout(int timeoutSec);
    void            SetCallback(TCPHandlerCallbackFunctor functor);
    std::error_code Run();
    std::error_code Close();

private:
    int         _timeoutSec  = YLG_NET_TCP_CONNECTION_TIMEOUT_SECOND_DFT;
    int         _threadCount = 0;
    std::string _listenAddress;
    uint16_t    _listenPort = 0;

    TCPHandlerCallbackFunctor _functor  = nullptr;
    event_base*               _base     = nullptr;
    evconnlistener*           _listener = nullptr;

    std::atomic_uint64_t       _handlerIndex = 0;
    std::vector<TCPHandlerPtr> _handlers;
};

using TCPServerPtr = std::shared_ptr<TCPServer>;

} // namespace net
} // namespace ylg

#endif
