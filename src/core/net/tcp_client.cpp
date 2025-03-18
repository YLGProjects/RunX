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

#include "core/net/tcp_client.h"
#include "core/error/error.h"
#include "core/log/log.h"
#include "core/net/message.h"
#include "core/net/tcp_connection.h"
#include "core/net/tcp_handler.h"
#include "internal/error.h"

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/util.h>

#include <memory.h>
#include <string>

namespace ylg {
namespace net {

TCPClient::TCPClient()
{
}

TCPClient::~TCPClient()
{
}

void TCPClient::ReadCallback(bufferevent* bev, void* ctx)
{
    auto       conn    = static_cast<TCPConnection*>(ctx);
    MessagePtr msg     = std::make_shared<Message>();
    auto       errcode = conn->Read(msg);
    if ((int)error::ErrorCode::TryAgain == errcode.value())
    {
        return;
    }

    if (!error::IsSuccess(errcode))
    {
        LOG_ERROR("failed to read data from connection:{}", conn->GetRemoteAddress());
    }

    auto handler = static_cast<TCPClient*>(conn->GetHandler());
    handler->_functor->HandleData(conn->shared_from_this(), msg);
}

void TCPClient::EventCallback(bufferevent* bev, short events, void* ctx)
{
    auto       conn   = static_cast<TCPConnection*>(ctx);
    TCPClient* client = (TCPClient*)conn->GetHandler();

    if (events & BEV_EVENT_CONNECTED)
    {
        conn->UpdateState(ConnectionState::Connected);
        client->_functor->OnConnection(conn->shared_from_this());
        return;
    }

    if (events & BEV_EVENT_EOF)
    {
        conn->UpdateState(ConnectionState::Disconnected);
        auto sharedConn = conn->shared_from_this();
        client->_functor->OnDisconnection(sharedConn);
        client->_connection.reset();
        return;
    }

    if (events & BEV_EVENT_ERROR)
    {
    }

    if (events & BEV_EVENT_TIMEOUT)
    {
        LOG_WARN("connection timeout. connection:{}", conn->ID());
    }
}

void TCPClient::CheckConnectionState(evutil_socket_t fd, short events, void* ctx)
{
    auto client = static_cast<TCPClient*>(ctx);

    LOG_DEBUG("tcp client check the connection state, remote server: {}:{}", client->_remoteIP, client->_remotePort);

    if (client->_connection == nullptr || client->_connection->State() != ConnectionState::Connected)
    {
        auto errcode = client->Reconnect();
        if (!ylg::error::IsSuccess(errcode))
        {
            LOG_WARN("failed to reconnect. remote server:{}:{}", client->_remoteIP, client->_remotePort);
        }
    }

    // set the next timer
    evtimer_add(client->_checkConnectionStateEvent, &client->_timeoutSeconds);
}

void TCPClient::SetTimeout(int timeoutSec)
{
    _timeoutSeconds.tv_sec = timeoutSec;
}

void TCPClient::SetCallback(TCPHandlerCallbackFunctor functor)
{
    _functor = functor;
}

std::error_code TCPClient::Connect(const std::string& ip, uint16_t port)
{
    _base = event_base_new();
    if (!_base)
    {
        LOG_ERROR("failed to create evnet base:{}:{}", ip, port);
        return error::ErrorCode::LibException;
    }

    _remoteIP   = ip;
    _remotePort = port;

    auto errcode = Reconnect();
    if (!ylg::error::IsSuccess(errcode))
    {
        return errcode;
    }

    _asyncRun = std::async(std::launch::async, &TCPClient::Run, this);
    return error::ErrorCode::Success;
}

void TCPClient::Close()
{
    if (!_base)
    {
        return;
    }

    event_base_loopbreak(_base);
    bufferevent_free(_bev);
    event_base_free(_base);

    _base = nullptr;
    _bev  = nullptr;

    _asyncRun.wait();
}

std::error_code TCPClient::Send(const Message& msg)
{
    if (_connection == nullptr)
    {
        return error::ErrorCode::ConnectionIsNotReady;
    }

    if (_connection->State() != ConnectionState::Connected)
    {
        return ylg::error::ErrorCode::ConnectionIsNotReady;
    }

    return _connection->Send(msg);
}

void TCPClient::Run()
{
    // set timer callback
    _checkConnectionStateEvent = evtimer_new(_base, &TCPClient::CheckConnectionState, this);
    evtimer_add(_checkConnectionStateEvent, &_timeoutSeconds);

    // start the event loop
    int exitedCode = 0;
    do {
        exitedCode = event_base_loop(_base, EVLOOP_NO_EXIT_ON_EMPTY);
    } while (exitedCode != -1);

    LOG_WARN("tcp client run exited. exited code:{}", exitedCode);
    bufferevent_free(_bev);
}

std::error_code TCPClient::Reconnect()
{
    evutil_addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    auto             remotePort = std::to_string(_remotePort);
    evutil_addrinfo* servinfo;

    if (getaddrinfo(_remoteIP.c_str(), remotePort.c_str(), &hints, &servinfo) != 0)
    {
        event_base_free(_base);
        return error::ErrorCode::ConnectionAborted;
    }

    evutil_addrinfo* p = nullptr;
    for (p = servinfo; p != nullptr; p = p->ai_next)
    {
        _bev = bufferevent_socket_new(_base, -1, BEV_OPT_CLOSE_ON_FREE);
        if (bufferevent_socket_connect(_bev, p->ai_addr, p->ai_addrlen) < 0)
        {
            bufferevent_free(_bev);
            continue;
        }

        auto conn = std::make_shared<TCPConnection>(-1, p->ai_addr, p->ai_addrlen);
        conn->UpdateState(ConnectionState::Connecting);
        conn->BindHandler(_bev, this);
        bufferevent_setcb(_bev, &TCPClient::ReadCallback, nullptr, &TCPClient::EventCallback, conn.get());
        bufferevent_enable(_bev, EV_READ | EV_WRITE);
        _connection = conn;
        break;
    }

    freeaddrinfo(servinfo);
    return ylg::internal::ErrorCode::Success;
}

} // namespace net
} // namespace ylg

