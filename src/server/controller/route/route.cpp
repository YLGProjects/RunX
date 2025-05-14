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

#include "server/controller/route/route.h"
#include "server/controller/configuration.h"
#include "server/controller/route/agent_session.h"

#include "internal/error.h"

#include "core/net/tcp_connection.h"

void Route::SaveConnection(ylg::net::TCPConnectionPtr conn)
{
    _conns.Push(conn->ID(), conn);
}

std::error_code Route::CreateLocalSession(ylg::net::TCPConnectionPtr conn, const std::string& agentID)
{
    auto session = std::make_shared<AgentSession>();

    session->_agentID    = agentID;
    session->_connection = conn;

    auto value    = session->ToJSON();
    auto agentKey = _routeRootKey + "/" + session->_agentID;
    auto ec       = _localConfig->_ctx->GetRegistry()->Set(agentKey, value);
    if (!ylg::internal::IsSuccess(ec))
    {
        LOG_WARN("failed to set agent info in the registry. key:{}, errmsg:{}", agentKey, ec.message());
    }

    _connAgentIDs.Push(conn->ID(), session->_agentID);
    _agents.Push(session->_agentID, session);

    return ylg::internal::ErrorCode::SUCCESS;
}

AgentSessionPtr Route::FindAgentSession(const std::string& agentID)
{
    return _agents.Find(agentID);
}

std::error_code Route::RemoveLocalSession(ylg::net::TCPConnectionPtr conn)
{
    if (!_connAgentIDs.Exists(conn->ID()))
    {
        return ylg::error::ErrorCode::SYSTEM_NOT_FOUND;
    }

    auto agentID = _connAgentIDs.Find(conn->ID());
    if (!agentID.empty())
    {
        _agents.Delete(agentID);
    }

    return ylg::internal::ErrorCode::SUCCESS;
}

std::error_code Route::RemoveAgentSession(const std::string& agentID)
{
    auto agentSession = _agents.Remove(agentID);
    if (agentSession == nullptr)
    {
        return ylg::error::ErrorCode::SYSTEM_NOT_FOUND;
    }

    _connAgentIDs.Delete(agentSession->_connection->ID());
    return ylg::internal::ErrorCode::ERROR;
}

std::error_code Route::Run(std::shared_ptr<Configuration> cfg)
{
    _localConfig  = cfg;
    _routeRootKey = _localConfig->_ctx->GetRegistry()->GetRootKey() + "/routes";
    return ylg::internal::ErrorCode::SUCCESS;
}

void Route::Close()
{
    _connAgentIDs.Clean();
    _agents.Clean();
}

