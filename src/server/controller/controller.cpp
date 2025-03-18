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

#include "server/controller/controller.h"

#include "internal/controller_protocol.h"
#include "internal/error.h"

#include "core/error/error.h"
#include "core/log/log.h"
#include "core/net/message.h"
#include "core/net/tcp_connection.h"
#include "core/net/tcp_server.h"

Controller::Controller()
{
    _route = std::make_shared<Route>();
    _tasks = std::make_shared<ylg::assist::ExecutionMultiQueue>("controller_task_queue",
                                                                SERVER_CONTROLLER_TASK_QUEUE_SIZE_DFT,
                                                                SERVER_CONTROLLER_TASK_QUEUE_COUNT_DFT);
}

void Controller::OnConnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("new connection.{}", conn->ID());
    auto errcode = _route->CreateLocalSession(conn);
    if (!ylg::internal::IsSuccess(errcode))
    {
        LOG_WARN("failed to create local session for the connection:{}", conn->ID());
    }

    LOG_DEBUG("created local session for the connection:{}", conn->ID());
}

void Controller::OnDisconnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("connection disconnection.{}", conn->ID());
    auto errcode = _route->RemoveLocalSession(conn);
    if (!ylg::internal::IsSuccess(errcode))
    {
        LOG_WARN("failed to remove local session for the connection:{}", conn->ID());
    }

    LOG_DEBUG("removed the local session for the connection:{}", conn->ID());
}

void Controller::HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg)
{
    LOG_DEBUG("new message{} size:{}", msg->GetPayload(), msg->GetPayloadSize());

    auto task = [&]() {
        auto header = msg->GetHeader();
        auto type   = (ylg::internal::MessageType)header._msgType;

        auto iter = _processors.find(type);
        if (iter != _processors.end())
        {
            LOG_WARN("invalid message type:0x%x", header._msgType);
            return;
        }

        ylg::net::MessagePtr rsp = std::make_shared<ylg::net::Message>();

        auto processor = iter->second;
        auto errcode   = processor->Do(msg, rsp);
        if (!ylg::internal::IsSuccess(errcode))
        {
            return;
        }

        errcode = conn->Send(rsp);
        if (!ylg::error::IsSuccess(errcode))
        {
            LOG_ERROR("can not send send to remote server. errcode:{}", errcode.value());
            return;
        }
    };

    auto errcode = _tasks->Enqueue(task);
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_WARN("can not enqueue controllor task queue. errmsg:{}", errcode.message());
    }
}

void Controller::Run(const std::string& listenIP, uint16_t listenPort)
{
    _listenIP   = listenIP;
    _listenPort = listenPort;

    auto runFunctor = [&]() {
        _server = std::make_shared<ylg::net::TCPServer>(_listenIP, _listenPort);
        _server->SetCallback(shared_from_this());
        auto errcode = _server->Run();
        if (!ylg::error::IsSuccess(errcode))
        {
            LOG_FATAL("the tcp server can not be started. errcode:{}", errcode.value());
        }
    };

    _asyncRun = std::async(std::launch::async, runFunctor);
}

void Controller::Close()
{
    auto errcode = _server->Close();
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_WARN("failed to stop tcp server. errcode:{}", errcode.value());
    }

    _asyncRun.wait();
}

std::error_code Controller::PostToAgent(const std::vector<std::string>& agentIDs, const char* data, uint32_t size)
{
    auto agentSession = _route->FindAgentSession("");

    ylg::net::Header header;
    header._dataSize = size;
    header._msgType  = (uint32_t)ylg::internal::MessageType::Ping;

    ylg::net::Hton(header);

    ylg::net::Message msg(header, data, size);

    auto errcode = agentSession->_connection->Send(msg);
    if (!ylg::internal::IsSuccess(errcode))
    {
        return errcode;
    }

    return ylg::internal::ErrorCode::Success;
}

void Controller::RegisterProcessor()
{
}

