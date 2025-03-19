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

#ifndef _YLG_INTERNAL_CONTROLLER_PROTOCOL_H_
#define _YLG_INTERNAL_CONTROLLER_PROTOCOL_H_

#include "core/net/message.h"

#include <cstdint>
#include <string>
#include <system_error>

namespace ylg {
namespace internal {

#define PROTOCOL_VERSION_01 0x01

enum class MessageType : uint32_t
{
    Ping                     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x001),
    Pong                     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x002),
    AuthRequest              = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x003),
    AuthResponse             = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x004),
    RegisterAgentRequest     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x005),
    RegisterAgentResponse    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x006),
    UnregisterAgentRequest   = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x007),
    UnregisterAgentResponse  = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x008),
    ReportAgentState         = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x009),
    RegisterPluginRequest    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00A),
    RegisterPluginResponse   = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00B),
    UnregisterPluginRequest  = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00C),
    UnregisterPluginResponse = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00D),
    ReportPluginState        = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00E),
    OperatePluginRequest     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00F),
    OperatePluginResponse    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x010),
};

enum class AgentState : uint32_t
{
    Offline = 0x01,
    Online  = 0x02,
};

enum class AgentPluginState : uint32_t
{
    Offline = 0x01,
    Online  = 0x02,
};

struct PluginBaseInfo
{
    std::string _name;
    std::string _version;
    std::string _logLevel;
    std::string _installedLocation;
    uint64_t    _installedTimestamp = 0;
    uint64_t    _startedTimestamp   = 0;
    uint64_t    _runningDuration    = 0;
};

struct AuthRequest
{
    std::string _agentID;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct AuthResponse
{
    std::string _agentID;
    bool        _valid = false;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct RegisterAgentRequest
{
    std::string _ip;
    std::string _mac;
    std::string _netDevName;
    std::string _machineID;
    std::string _hostName;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct RegisterAgentResponse
{
    std::string _agentID;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct UnregisterAgentRequest
{
    std::string _agentID;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct UnregisterAgentResponse
{
    std::string _agentID;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct ReportAgentState
{
    std::string _agentID;
    AgentState  _state;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct RegisterPluginRequest
{
    std::string _agentID;

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct RegisterPluginResponse
{
    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct UnregisterPluginRequest
{
    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct UnregisterPluginResponse
{
    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct ReportPluginState
{

    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct OperatePluginRequest
{
    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

struct OperatePluginResponse
{
    std::error_code ToJSON(std::string& data);
    std::error_code LoadJSON(const std::string& data);
};

} // namespace internal
} // namespace ylg

#endif

