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

#include "core/net/tcp_connection.h"
#include "core/assist/string.h"
#include "core/assist/time.h"
#include "core/error/error.h"
#include "core/log/log.h"
#include "core/net/message.h"

#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>

namespace ylg {
namespace net {

TCPConnection::TCPConnection(evutil_socket_t fd, sockaddr* address, int socklen)
{
    _fd                      = fd;
    char host[NI_MAXHOST]    = {0};
    char service[NI_MAXSERV] = {0};
    int  flags               = NI_NUMERICHOST | NI_NUMERICSERV;
    if (getnameinfo(address, sizeof(sockaddr_in), host, NI_MAXHOST, service, NI_MAXSERV, flags) != 0)
    {
        throw std::runtime_error("getnameinfo() failed");
    }

    _remoteIP   = host;
    _remotePort = std::atoi(service);
    _id         = assist::FormatString("%s-%d", _remoteIP.c_str(), _remotePort);
}

TCPConnection::~TCPConnection()
{
    LOG_DEBUG("connection is disconnected. {}", _id);

    if (_bev)
    {
        bufferevent_free(_bev);
        _bev = nullptr;
    }
}

const std::string& TCPConnection::ID()
{
    return _id;
}

void TCPConnection::UpdateState(ConnectionState state)
{
    _state.store(state);
}

bool TCPConnection::IsTimeout(int timeoutSec)
{
    auto duration = assist::TimestampTickCountSecond() - _lastReadTimestamp;
    return duration >= timeoutSec;
}

ConnectionState TCPConnection::State()
{
    return _state;
}

void TCPConnection::BindHandler(bufferevent* bev, void* handler)
{
    _bev     = bev;
    _handler = handler;
}

void* TCPConnection::GetHandler()
{
    return _handler;
}

std::string TCPConnection::GetRemoteAddress()
{
    return assist::FormatString("%s:%d", _remoteIP.c_str(), _remotePort);
}

std::error_code TCPConnection::Read(MessagePtr msg)
{
    evbuffer* buffer = bufferevent_get_input(_bev);
    if (Message::MESSAGE_HEADER_SIZE > evbuffer_get_length(buffer))
    {
        LOG_DEBUG("evbuffer length less than header size");
        return error::ErrorCode::TryAgain;
    }

    Header header;
    int    length = evbuffer_copyout(buffer, (void*)&header, Message::MESSAGE_HEADER_SIZE);
    if (Message::MESSAGE_HEADER_SIZE > length)
    {
        LOG_DEBUG("evbuffer copied size less than header size");
        return error::ErrorCode::TryAgain;
    }

    Ntoh(header);

    uint32_t totalSize = header._dataSize + Message::MESSAGE_HEADER_SIZE;
    if (totalSize > Message::MAX_MESSAGE_SIZE)
    {
        LOG_DEBUG("total size {} more than max message size {}.", totalSize, (uint64_t)Message::MAX_MESSAGE_SIZE);
        return error::ErrorCode::ReceivedTooLarge;
    }

    char* msgBuffer = (char*)evbuffer_pullup(buffer, totalSize);
    if (!msgBuffer)
    {
        return error::ErrorCode::TryAgain;
    }

    LOG_DEBUG("received, body size:{}, total size:{}", header._dataSize, totalSize);
    msg->Reset(header, msgBuffer + Message::MESSAGE_HEADER_SIZE, header._dataSize);
    evbuffer_drain(buffer, totalSize);

    _lastReadTimestamp = assist::TimestampTickCountSecond();
    return error::ErrorCode::Success;
}

std::error_code TCPConnection::Send(const Message& msg)
{
    LOG_DEBUG("send data. size:{}, remote address:{}", msg.GetDataSize(), GetRemoteAddress());
    int errcode = bufferevent_write(_bev, msg.GetData(), msg.GetDataSize());
    if (errcode)
    {
        return error::ErrorCode::WritedException;
    }
    return error::ErrorCode::Success;
}

std::error_code TCPConnection::Send(const MessagePtr msg)
{
    return Send(*msg);
}

} // namespace net
} // namespace ylg

