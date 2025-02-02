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

#ifndef _YLG_NET_HTTP_CONTEXT_H_
#define _YLG_NET_HTTP_CONTEXT_H_

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace ylg {
namespace net {

using HTTPURI   = std::string;
using Parameter = std::map<std::string, std::string>;

enum class HTTPMethod
{
    GET,
    POST,
    PUT,
    DELETE
};

struct Parameters
{
    Parameter _headerParameters;
    Parameter _queryParamters;
    Parameter _pathParameters;
};

using HTTPMethodHandler = std::function<void(const Parameters& inParameters,
                                             Parameters&       outParameters,
                                             int& status, std::string& response)>;

struct RegisteredHandler
{
    std::string       _uri;
    HTTPMethod        _method;
    HTTPMethodHandler _handler;
};

using RegisteredHandlerPtr = std::shared_ptr<RegisteredHandler>;

} // namespace net
} // namespace ylg

#endif

