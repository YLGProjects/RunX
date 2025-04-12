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

#include "internal/controller.h"

#include "core/parser/json.h"

namespace ylg {
namespace internal {

std::string ServiceInfo::ToJSON()
{
    rj::Document doc(rj::kObjectType);

    auto& allocator = doc.GetAllocator();

    doc.AddMember("service_id", _serviceID, allocator);
    doc.AddMember("service_name", _serviceName, allocator);
    doc.AddMember("listen_address", _listeningAddress, allocator);
    doc.AddMember("api_address", _apiAddress, allocator);
    doc.AddMember("load", _load, allocator);
    doc.AddMember("updated_timestamp", _updatedTimestamp, allocator);

    return ylg::parser::JToString(doc);
}

bool ServiceInfo::LoadJSON(const std::string& json, std::string& errMsg)
{
    rj::Document doc;
    if (!ylg::parser::JLoad(json, doc, &errMsg))
    {
        return false;
    }

    auto serviceID = ylg::parser::JHelper<std::string>::Get(doc, "service_id");
    if (serviceID._ok)
    {
        _serviceID = serviceID._value;
    }

    auto serviceName = ylg::parser::JHelper<std::string>::Get(doc, "service_name");
    if (serviceName._ok)
    {
        _serviceName = serviceName._value;
    }

    auto listenAddress = ylg::parser::JHelper<std::string>::Get(doc, "listen_address");
    if (listenAddress._ok)
    {
        _listeningAddress = listenAddress._value;
    }

    auto apiAddress = ylg::parser::JHelper<std::string>::Get(doc, "api_address");
    if (apiAddress._ok)
    {
        _apiAddress = apiAddress._value;
    }

    auto load = ylg::parser::JHelper<float>::Get(doc, "load");
    if (load._ok)
    {
        _load = load._value;
    }

    auto updatedTimestamp = ylg::parser::JHelper<uint64_t>::Get(doc, "updated_timestamp");
    if (updatedTimestamp._ok)
    {
        _updatedTimestamp = updatedTimestamp._value;
    }

    return true;
}

} // namespace internal
} // namespace ylg
