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

#ifndef _YLG_CORE_NET_TCP_CONNECTION_H_
#define _YLG_CORE_NET_TCP_CONNECTION_H_

#include "core/net/message.h"

#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/util.h>

#include <cstdint>
#include <memory>
#include <string>
#include <system_error>

namespace ylg {
namespace net {

class TCPConnection final
{
public:
    TCPConnection(evutil_socket_t fd, sockaddr* address, int socklen);
    ~TCPConnection();

public:
    void BindHandler(bufferevent* bev, void* handler);

public:
    const std::string& ID();
    void*              GetHandler();
    std::string        GetRemoteAddress();
    std::error_code    Read(Message& msg);
    std::error_code    Send(const Message& msg);

private:
    std::string     _id;
    evutil_socket_t _fd = EVUTIL_INVALID_SOCKET;

    std::string _remoteIP;
    uint16_t    _remotePort = 0;

    void*        _handler = nullptr;
    bufferevent* _bev     = nullptr;
};

using TCPConnectionPtr = std::shared_ptr<TCPConnection>;

} // namespace net
} // namespace ylg

#endif

