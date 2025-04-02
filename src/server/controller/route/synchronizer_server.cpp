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

#include "server/controller/route/synchronizer_server.h"

#include "core/log/log.h"
#include "internal/controller.h"
#include "internal/error.h"

SynchronizerServer::SynchronizerServer()
{
    _tasks = std::make_shared<ylg::assist::ExecutionMultiQueue>("synchronizer-server-task-queue",
                                                                SERVER_CONTROLLER_ROUTE_SYNCHRONIZER_SERVER_TASK_QUEUE_SIZE_DFT,
                                                                SERVER_CONTROLLER_ROUTE_SYNCHRONIZER_SERVER_TASK_QUEUE_COUNT_DFT);
}

void SynchronizerServer::OnConnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("new connection:{}", conn->ID());
    _conns.Push(conn->ID(), conn);
}

void SynchronizerServer::OnDisconnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("connection disconnected:{}", conn->ID());
    _conns.Delete(conn->ID());
}

void SynchronizerServer::HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg)
{
    LOG_DEBUG("new message, remote server:{} size:{}", conn->GetRemoteAddress(), msg->GetPayloadSize());

    auto task = [=]() {
        const auto& header = msg->GetHeader();
        auto        type   = (ylg::internal::MessageType)header._msgType;

        switch (type)
        {
        case ylg::internal::MessageType::ROUTE_BROADCAST_REQUEST:
            break;
        case ylg::internal::MessageType::ROUTE_SYNC_REQUEST:
            break;
        default:
            break;
        }
    };

    auto errcode = _tasks->Enqueue(task);
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_WARN("can not enqueue synchronizer task queue. errmsg:{}", errcode.message());
    }
}

void SynchronizerServer::Run(const std::string& listenIP, uint16_t listenPort)
{
    _listenIP   = listenIP;
    _listenPort = listenPort;

    auto runFunctor = [&]() {
        _server = std::make_shared<ylg::net::TCPServer>(_listenIP, _listenPort);
        _server->SetCallback(shared_from_this());
        auto errcode = _server->Run();
        if (!ylg::error::IsSuccess(errcode))
        {
            LOG_FATAL("can not start synchronizer server. errcode:{}", errcode.value());
        }
    };

    _asyncRun = std::async(std::launch::async, runFunctor);
}

void SynchronizerServer::Close()
{
    auto errcode = _server->Close();
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_WARN("failed to stop synchronizer server. errcode:{}", errcode.value());
    }

    _asyncRun.wait();
}
