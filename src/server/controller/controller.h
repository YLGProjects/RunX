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

#ifndef _YLG_SERVER_CONTROLLER_H_
#define _YLG_SERVER_CONTROLLER_H_

#include "server/controller/processor/processor.h"
#include "server/controller/route/route.h"

#include "internal/controller.h"

#include "core/assist/execution_multi_queue.h"
#include "core/net/tcp_connection.h"
#include "core/net/tcp_handler.h"
#include "core/net/tcp_server.h"

#include <future>
#include <map>
#include <memory>

// clang-format off

#define SERVER_CONTROLLER_TASK_QUEUE_SIZE_DFT  40960
#define SERVER_CONTROLLER_TASK_QUEUE_COUNT_DFT 10

// clang-format on

struct Configuration;
class Controller final : public ylg::net::TCPHandlerCallback, public std::enable_shared_from_this<Controller>
{
public:
    Controller();
    ~Controller() = default;

public:
    virtual void OnConnection(ylg::net::TCPConnectionPtr conn) override;
    virtual void OnDisconnection(ylg::net::TCPConnectionPtr conn) override;
    virtual void HandleData(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg) override;

public:
    void            Run(std::shared_ptr<Configuration> cfg);
    void            Close();
    std::error_code PostToAgent(const std::vector<std::string>& agentIDs, ylg::internal::MessageType msgType, const char* data, uint32_t size);

private:
    ylg::net::MessagePtr RegisterAgent(ylg::net::TCPConnectionPtr conn, const ylg::net::MessagePtr msg);
    void                 RegisterProcessor();

private:
    std::future<void>                                     _asyncRun;
    std::shared_ptr<Configuration>                        _localConfig;
    ylg::assist::ExecutionMultiQueuePtr                   _tasks  = nullptr;
    ylg::net::TCPServerPtr                                _server = nullptr;
    RoutePtr                                              _route  = nullptr;
    std::map<ylg::internal::MessageType, MsgProcessorPtr> _processors;
};

using ControllerPtr = std::shared_ptr<Controller>;

#endif

