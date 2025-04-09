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

#ifndef _YLG_INTERNAL_CONTROLLER_H_
#define _YLG_INTERNAL_CONTROLLER_H_

#include "core/net/message.h"

#include "internal/controller.pb.h"

#include <cstdint>

namespace ylg {
namespace internal {

#define PROTOCOL_VERSION_01 0x01

enum class MessageType : uint32_t
{
    // CONTROLLER: YLG_NET_MESSAGE_PROTOCOL_BASE + [0x001,0x100)
    PING                       = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x001),
    PONG                       = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x002),
    AUTH_REQUEST               = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x003),
    AUTH_RESPONSE              = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x004),
    REGISTER_AGENT_REQUEST     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x005),
    REGISTER_AGENT_RESPONSE    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x006),
    UNREGISTER_AGENT_REQUEST   = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x007),
    UNREGISTER_AGENT_RESPONSE  = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x008),
    REPORT_AGENT_STATE         = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x009),
    REGISTER_PLUGIN_REQUEST    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00A),
    REGISTER_PLUGIN_RESPONSE   = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00B),
    UNREGISTER_PLUGIN_REQUEST  = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00C),
    UNREGISTER_PLUGIN_RESPONSE = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00D),
    REPORT_PLUGIN_STATE        = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00E),
    OPERATE_PLUGIN_REQUEST     = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x00F),
    OPERATE_PLUGIN_RESPONSE    = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x010),

    // ROUTE: YLG_NET_MESSAGE_PROTOCOL_BASE + [0x100, 0x200)
    ROUTE_BROADCAST_REQUEST  = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x100),
    ROUTE_BROADCAST_RESPONSE = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x101),
    ROUTE_SYNC_REQUEST       = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x102),
    ROUTE_SYNC_RESPONSE      = (YLG_NET_MESSAGE_PROTOCOL_BASE + 0x103),
};

struct ServiceInfo
{
    std::string _serviceID;
    std::string _serviceName;
    std::string _listeningAddress;
    std::string _apiAddress;

    // load value is between [0, 100]
    float    _load             = 0.0;
    uint64_t _updatedTimestamp = 0;

    std::string ToJSON();
    bool        LoadJSON(const std::string& json, std::string& errMsg);
};

} // namespace internal
} // namespace ylg

#endif

