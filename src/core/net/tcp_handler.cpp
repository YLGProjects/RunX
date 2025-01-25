#include "core/net/tcp_handler.h"
#include "core/log/log.h"
#include "core/net/error.h"
#include "core/net/message.h"
#include "core/net/tcp_connection.h"

#include <bits/types/struct_timeval.h>
#include <event2/bufferevent.h>
#include <event2/event.h>

#include <future>

namespace ylg {
namespace net {

TCPHandler::TCPHandler()
{
}

TCPHandler::~TCPHandler()
{
}

void TCPHandler::ReadCallback(bufferevent* bev, void* ctx)
{
    TCPConnection* connection = static_cast<TCPConnection*>(ctx);

    Message msg;
    auto    errcode = connection->Read(msg);

    if ((int)ErrorCode::TryAgain == errcode.value())
    {
        LOG_WARN("more date need to be read from the connection:{}", connection->ID());
        return;
    }

    if (!IsSuccess(errcode))
    {
        LOG_ERROR("failed to read data from connection:{}, errcode:{}", connection->GetRemoteAddress(), errcode.value());
    }

    LOG_DEBUG("readed a message. connection:{}", connection->ID());
    auto handler = static_cast<TCPHandler*>(connection->GetHandler());
    handler->_functor->HandleData(msg);
}

void TCPHandler::EventCallback(bufferevent* bev, short events, void* ctx)
{
    TCPConnection* connection = static_cast<TCPConnection*>(ctx);
    if (events & BEV_EVENT_EOF)
    {
        auto handler = static_cast<TCPHandler*>(connection->GetHandler());
        handler->_functor->OnDisconnection(connection);
        handler->_connections.Delete(connection->ID());
        bufferevent_free(bev);
        LOG_DEBUG("connection is disconnected. {}", connection->ID());
        delete connection;
        return;
    }

    if (events & BEV_EVENT_ERROR)
    {
        LOG_ERROR("make some exception from bufferevent");
    }
}

void TCPHandler::SetCallback(TCPHandlerCallbackFunctor functor)
{
    _functor = functor;
}

void TCPHandler::BindConnection(evutil_socket_t fd, sockaddr* address, int socklen)
{
    auto connection = new TCPConnection(fd, address, socklen);
    auto bev        = bufferevent_socket_new(_base, fd, BEV_OPT_CLOSE_ON_FREE);

    _functor->OnConnection(connection);

    bufferevent_setcb(bev, ReadCallback, nullptr, EventCallback, connection);
    bufferevent_setwatermark(bev, EV_READ, Message::MESSAGE_HEADER_SIZE, 10 * 1024 * 1024);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    timeval timeout;
    timeout.tv_sec  = 10;
    timeout.tv_usec = 0;
    bufferevent_set_timeouts(bev, &timeout, &timeout);

    connection->BindHandler(bev, this);
    _connections.Push(connection->ID(), connection);
}

std::error_code TCPHandler::Start()
{
    _base = event_base_new();
    if (!_base)
    {
        LOG_ERROR("failed to create event base");
        return MakeError(ErrorCode::LibException);
    }

    _asyncRun = std::async(std::launch::async, &TCPHandler::Run, this);

    return MakeSuccess();
}

std::error_code TCPHandler::Stop()
{
    if (!_base)
    {
        return MakeSuccess();
    }

    event_base_loopbreak(_base);
    event_base_free(_base);

    _base = nullptr;

    return MakeSuccess();
}

void TCPHandler::Run()
{
    int exitedCode = 0;
    do {
        exitedCode = event_base_dispatch(_base);
    } while (exitedCode != -1);

    LOG_WARN("tcp handler run exited. exited code:{}", exitedCode);
}

} // namespace net
} // namespace ylg

