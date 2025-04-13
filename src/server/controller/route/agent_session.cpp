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

#include "server/controller/route/agent_session.h"

#include "core/parser/json.h"

std::string AgentSession::ToJSON()
{
    rj::Document doc(rj::kObjectType);
    auto&        allocator = doc.GetAllocator();

    doc.AddMember("agent_id", _agentID, allocator);
    doc.AddMember("service_id", _serviceID, allocator);
    doc.AddMember("cpu_usage", _cpuUsage, allocator);
    doc.AddMember("mem_usage", _memUsage, allocator);
    doc.AddMember("created_timestamp", _createdTimestamp, allocator);

    return ylg::parser::JToString(doc);
}

bool AgentSession::LoadJSON(const std::string& json, std::string& errMsg)
{
    rj::Document doc;
    if (!ylg::parser::JLoad(json, doc, &errMsg))
    {
        return false;
    }

    auto agentID = ylg::parser::JHelper<std::string>::Get(doc, "agent_id");
    if (!agentID)
    {
        return false;
    }
    _agentID = agentID._value;

    auto serviceID = ylg::parser::JHelper<std::string>::Get(doc, "service_id");
    if (!serviceID)
    {
        return false;
    }
    _serviceID = serviceID._value;

    auto cpuUsage = ylg::parser::JHelper<float>::Get(doc, "cpu_usage");
    if (!cpuUsage)
    {
        return false;
    }
    _cpuUsage = cpuUsage._value;

    auto memUsage = ylg::parser::JHelper<float>::Get(doc, "mem_usage");
    if (!memUsage)
    {
        return false;
    }
    _memUsage = memUsage._value;

    auto createdTimestamp = ylg::parser::JHelper<uint64_t>::Get(doc, "created_timestamp");
    if (!createdTimestamp)
    {
        return false;
    }
    _createdTimestamp = createdTimestamp._value;

    return true;
}
