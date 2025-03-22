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

#include "agent/controller/controller.h"
#include "agent/command/auth_request.h"
#include "agent/command/auth_respond.h"
#include "agent/command/operate_plugin_request.h"
#include "agent/command/ping_request.h"
#include "agent/command/register_agent_respond.h"

#include "internal/controller.h"
#include "internal/error.h"

#include "core/log/log.h"
#include "core/net/message.h"
#include "core/net/tcp_client.h"
#include "core/net/tcp_connection.h"

#include <cstdint>
#include <memory>

Controller::Controller()
{
    _tasks = std::make_shared<ylg::assist::ExecutionMultiQueue>("controller_task_queue",
                                                                AGENT_CONTROLLER_TASK_QUEUE_SIZE_DFT,
                                                                AGENT_CONTROLLER_TASK_QUEUE_COUNT_DFT);
}

Controller::~Controller()
{
}

void Controller::OnConnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("connected to the remote server. connection:{}", conn->ID());
}

void Controller::OnDisconnection(ylg::net::TCPConnectionPtr conn)
{
    LOG_DEBUG("disconnected with the remote server. connection:{}", conn->ID());
}

void Controller::HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg)
{
    auto header = msg->GetHeader();
    auto type   = (ylg::internal::MessageType)header._msgType;

    auto iter = _commands.find(type);
    if (iter == _commands.end())
    {
        LOG_WARN("invalid message type:0x{:04X}", header._msgType);
        return;
    }
    auto processor = iter->second;

    auto task = [=]() {
        auto errcode = processor->Do(msg);
        if (!ylg::internal::IsSuccess(errcode))
        {
            return;
        }
    };

    auto errcode = _tasks->Enqueue(task);
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_WARN("can not enqueue controllor task queue. errmsg:{}", errcode.message());
    }
}

void Controller::Run(const std::string& remoteIP, uint16_t remotePort)
{
    _remoteIP   = remoteIP;
    _remotePort = remotePort;

    _client = std::make_shared<ylg::net::TCPClient>();
    _client->SetCallback(shared_from_this());

    RegisterCommands();

    auto errcode = _client->Connect(_remoteIP, _remotePort);
    if (!ylg::error::IsSuccess(errcode))
    {
        LOG_FATAL("can not connect the remote server. address:{}:{}", _remoteIP, _remotePort);
    }
}

void Controller::Close()
{
    if (!_client)
    {
        return;
    }

    _client->Close();
    _commands.clear();
}

void Controller::RegisterCommands()
{
    _commands[ylg::internal::MessageType::Ping]                  = std::make_shared<PingRequestCMD>();
    _commands[ylg::internal::MessageType::RegisterAgentResponse] = std::make_shared<RegisterAgentRespondCMD>();
    _commands[ylg::internal::MessageType::AuthRequest]           = std::make_shared<AuthRequestCMD>();
    _commands[ylg::internal::MessageType::AuthResponse]          = std::make_shared<AuthRespondCMD>();
    _commands[ylg::internal::MessageType::OperatePluginRequest]  = std::make_shared<OperatePluginRequestCMD>();
}

