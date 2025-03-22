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
    BuildID();
}

TCPConnection::~TCPConnection()
{
    LOG_DEBUG("connection is disconnected. {}", _id);

    if (_bev)
    {
        bufferevent_disable(_bev, EV_WRITE | EV_READ);
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
    if (0 == _lastReadTimestamp)
    {
        _lastReadTimestamp = assist::TimestampTickCountSecond();
        return false;
    }

    // A timeout is only recognized if it exceeds the timeout period five times.
    auto duration = assist::TimestampTickCountSecond() - _lastReadTimestamp;
    auto timeout  = timeoutSec * 5;
    LOG_DEBUG("check timeout. duration: {}, timeout seconds: {}, connection: {}", duration, timeout, ID());
    return duration >= timeout;
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
        LOG_WARN("total size {} more than max message size {}.", totalSize, (uint64_t)Message::MAX_MESSAGE_SIZE);
        return error::ErrorCode::ReceivedTooLarge;
    }

    if (header._magic != YLG_NET_MESSAGE_MAGIC)
    {
        LOG_WARN("invalid connection: {}, magic: 0x{:04X}", ID(), header._magic);
        return error::ErrorCode::InvalidMagic;
    }

    _lastReadTimestamp = assist::TimestampTickCountSecond();
    UpdateState(ConnectionState::Connected);

    char* msgBuffer = (char*)evbuffer_pullup(buffer, totalSize);
    if (!msgBuffer)
    {
        LOG_DEBUG("no more data to read, connection: {}", ID());
        return error::ErrorCode::TryAgain;
    }

    LOG_DEBUG("received, body size:{}, total size:{}", header._dataSize, totalSize);
    msg->Reset(header, msgBuffer + Message::MESSAGE_HEADER_SIZE, header._dataSize);
    evbuffer_drain(buffer, totalSize);

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

void TCPConnection::BuildID()
{
    _id = assist::FormatString("%s-%d", _remoteIP.c_str(), _remotePort);
    assist::Trim(_id, ":-.");
}

} // namespace net
} // namespace ylg

