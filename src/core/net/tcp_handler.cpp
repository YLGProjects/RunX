#include "core/net/tcp_handler.h"
#include "core/error/error.h"
#include "core/log/log.h"
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

void TCPHandler::CheckConnectionState(evutil_socket_t fd, short events, void* ctx)
{
    auto server = static_cast<TCPHandler*>(ctx);

    LOG_DEBUG("tcp server handler check the connection state, connection count: {}", server->_connections.Count());

    evtimer_add(server->_checkConnectionStateEvent, &server->_timeoutSeconds);
}

void TCPHandler::SetTimeout(int timeoutSec)
{
    _timeoutSeconds.tv_sec = timeoutSec;
}
void TCPHandler::ReadCallback(bufferevent* bev, void* ctx)
{
    TCPConnection* conn = static_cast<TCPConnection*>(ctx);

    MessagePtr msg     = std::make_shared<Message>();
    auto       errcode = conn->Read(msg);

    if ((int)error::ErrorCode::TryAgain == errcode.value())
    {
        LOG_WARN("more date need to be read from the connection:{}", conn->ID());
        return;
    }

    if (!error::IsSuccess(errcode))
    {
        LOG_ERROR("failed to read data from connection:{}, errcode:{}", conn->GetRemoteAddress(), errcode.value());
    }

    LOG_DEBUG("readed a message. connection:{}", conn->ID());
    auto handler = static_cast<TCPHandler*>(conn->GetHandler());
    handler->_functor->HandleData(conn->shared_from_this(), msg);
}

void TCPHandler::EventCallback(bufferevent* bev, short events, void* ctx)
{
    TCPConnection* conn = static_cast<TCPConnection*>(ctx);
    if (events & BEV_EVENT_EOF)
    {
        auto handler = static_cast<TCPHandler*>(conn->GetHandler());
        handler->_functor->OnDisconnection(conn->shared_from_this());
        handler->_connections.Delete(conn->ID());
        bufferevent_free(bev);
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
    auto conn = std::make_shared<TCPConnection>(fd, address, socklen);
    auto bev  = bufferevent_socket_new(_base, fd, BEV_OPT_CLOSE_ON_FREE);

    _functor->OnConnection(conn);

    bufferevent_setcb(bev, ReadCallback, nullptr, EventCallback, conn.get());
    bufferevent_setwatermark(bev, EV_READ, Message::MESSAGE_HEADER_SIZE, 10 * 1024 * 1024);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    timeval timeout;
    timeout.tv_sec  = 10;
    timeout.tv_usec = 0;
    bufferevent_set_timeouts(bev, &timeout, &timeout);

    conn->BindHandler(bev, this);
    _connections.Push(conn->ID(), conn);
}

std::error_code TCPHandler::Start()
{
    _base = event_base_new();
    if (!_base)
    {
        LOG_ERROR("failed to create event base");
        return error::ErrorCode::LibException;
    }

    _asyncRun = std::async(std::launch::async, &TCPHandler::Run, this);

    return error::ErrorCode::Success;
}

std::error_code TCPHandler::Stop()
{
    if (!_base)
    {
        return error::ErrorCode::Success;
    }

    event_base_loopbreak(_base);
    event_free(_checkConnectionStateEvent);
    event_base_free(_base);

    _base                      = nullptr;
    _checkConnectionStateEvent = nullptr;

    return error::ErrorCode::Success;
}

void TCPHandler::Run()
{
    // set timer callback
    _checkConnectionStateEvent = evtimer_new(_base, &TCPHandler::CheckConnectionState, this);
    evtimer_add(_checkConnectionStateEvent, &_timeoutSeconds);

    // start event loop
    int exitedCode = 0;
    do {
        exitedCode = event_base_loop(_base, EVLOOP_NO_EXIT_ON_EMPTY);
    } while (exitedCode != -1);

    LOG_WARN("tcp handler run exited. exited code:{}", exitedCode);
}

} // namespace net
} // namespace ylg

