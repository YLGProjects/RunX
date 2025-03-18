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

#ifndef _YLG_AGENT_CONTROLLER_CONTROLLER_H_
#define _YLG_AGENT_CONTROLLER_CONTROLLER_H_

#include "agent/command/command.h"

#include "internal/controller_protocol.h"

#include "core/assist/execution_multi_queue.h"
#include "core/net/tcp_client.h"
#include "core/net/tcp_connection.h"

#include <cstdint>
#include <map>

// clang-format off

#define AGENT_CONTROLLER_TASK_QUEUE_SIZE_DFT  40960
#define AGENT_CONTROLLER_TASK_QUEUE_COUNT_DFT 10

// clang-format on

class Controller final : public ylg::net::TCPHandlerCallback, public std::enable_shared_from_this<Controller>

{
public:
    Controller();
    ~Controller();

public:
    virtual void OnConnection(ylg::net::TCPConnectionPtr conn) override;
    virtual void OnDisconnection(ylg::net::TCPConnectionPtr conn) override;
    virtual void HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg) override;

public:
    void Run(const std::string& remoteIP, uint16_t remotePort);
    void Close();

private:
    void RegisterCommands();

private:
    std::string                                      _remoteIP;
    uint16_t                                         _remotePort = 0;
    ylg::assist::ExecutionMultiQueuePtr              _tasks      = nullptr;
    std::map<ylg::internal::MessageType, CommandPtr> _commands;
    ylg::net::TCPClientPtr                           _client = nullptr;
};

using ControllerPtr = std::shared_ptr<Controller>;

#endif

