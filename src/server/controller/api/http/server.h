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

#ifndef _YLG_SERVER_CONTROLLER_API_HTTP_SERVER_H_
#define _YLG_SERVER_CONTROLLER_API_HTTP_SERVER_H_

#include "core/net/http_context.h"
#include "core/net/http_server.h"

#include <future>
#include <memory>

class HTTPAPIServer final
{
public:
    HTTPAPIServer();
    ~HTTPAPIServer();

public:
    void Run(const std::string& listenIP, uint16_t listenPort);
    void Close();

public:
    void Test(const ylg::net::Parameters& inParameters, ylg::net::Parameters& outParameters,
              int& status, std::string& response);

private:
    std::string             _listenIP;
    uint16_t                _listenPort = 0;
    std::future<void>       _asyncRun;
    ylg::net::HTTPServerPtr _httpServer = nullptr;
};

using HTTPAPIServerPtr = std::shared_ptr<HTTPAPIServer>;

#endif

