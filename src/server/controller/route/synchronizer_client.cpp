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

#include "server/controller/route/synchronizer_client.h"
#include "core/log/log.h"
#include "internal/controller.h"
#include "server/controller/route/agent_session.h"

#include "internal/error.h"

#include "core/net/message.h"
#include "core/net/tcp_client.h"
#include "core/net/tcp_connection.h"

SynchronizerClient::SynchronizerClient()
{
    _tasks = std::make_shared<ylg::assist::ExecutionMultiQueue>("controller_task_queue",
                                                                SERVER_CONTROLLER_ROUTE_SYNCHRONIZER_CLIENT_TASK_QUEUE_SIZE_DFT,
                                                                SERVER_CONTROLLER_ROUTE_SYNCHRONIZER_CLIENT_TASK_QUEUE_COUNT_DFT);
}

void SynchronizerClient::OnConnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("synchronizer client, connected. remote server:{}", conn->GetRemoteAddress());
}

void SynchronizerClient::OnDisconnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("synchronizer client, disconnected. remote server:{}", conn->GetRemoteAddress());
}

void SynchronizerClient::HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg)
{
    LOG_DEBUG("synchronizer client, received data.");
    const auto& header = msg->GetHeader();
    auto        type   = (ylg::internal::MessageType)header._msgType;

    auto task = [=]() {
        switch (type)
        {
        case ylg::internal::MessageType::ROUTE_BROADCAST_RESPONSE:
            break;
        case ylg::internal::MessageType::ROUTE_SYNC_RESPONSE:
            break;
        default:
            break;
        }
    };

    auto errcode = _tasks->Enqueue(task);
    if (!ylg::internal::IsSuccess(errcode))
    {
        LOG_WARN("can not enqueue synchronizer client task queue. errmsg:{}", errcode.message());
    }
}

std::error_code SynchronizerClient::PublishAgentSession(const std::vector<AgentSessionPtr>& agents)
{
    return ylg::internal::ErrorCode::SUCCESS;
}

std::error_code SynchronizerClient::Connect(const std::string& ip, uint16_t port)
{
    _remoteIP   = ip;
    _remotePort = port;

    _client = std::make_shared<ylg::net::TCPClient>();
    _client->SetCallback(shared_from_this());

    return _client->Connect(_remoteIP, _remotePort);
}

void SynchronizerClient::Close()
{
    if (_client == nullptr)
    {
        return;
    }

    _client->Close();
}
