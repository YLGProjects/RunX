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

#ifndef _YLG_NET_HTTP_SERVER_H_
#define _YLG_NET_HTTP_SERVER_H_

#include "core/net/http_context.h"

#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/http_struct.h>

#include <cstdint>
#include <memory>
#include <system_error>

namespace ylg {
namespace net {

class HTTPServer final
{
public:
    HTTPServer();
    ~HTTPServer();

public:
    std::error_code RegisterHandler(HTTPMethod method, const HTTPURI& uri,
                                    HTTPMethodHandler handler);
    void            Run(const std::string& listenIP, uint16_t listenPort);
    void            Close();

private:
    static void RequestHandler(evhttp_request* req, void* arg);

private:
    void UnsupportedRequestHandler(evhttp_request* req);
    void GetRequestHandler(evhttp_request* req);
    void PostRequestHandler(evhttp_request* req);
    void DeleteRequestHandler(evhttp_request* req);
    void PutRequestHandler(evhttp_request* req);

private:
    std::map<HTTPURI, RegisteredHandlerPtr> _getURIHandlers;
    std::map<HTTPURI, RegisteredHandlerPtr> _postURIHandlers;
    std::map<HTTPURI, RegisteredHandlerPtr> _deleteURIHandlers;
    std::map<HTTPURI, RegisteredHandlerPtr> _putURIHandlers;
    std::string                             _listenIP;
    uint16_t                                _listenPort = 0;
    event_base*                             _base       = nullptr;
    evhttp*                                 _httpServer = nullptr;
};

using HTTPServerPtr = std::shared_ptr<HTTPServer>;

} // namespace net
} // namespace ylg

#endif

