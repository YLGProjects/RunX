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

#include "server/api/http/server.h"
#include "core/net/http_server.h"

HTTPAPIServer::HTTPAPIServer() {}
HTTPAPIServer::~HTTPAPIServer() {}

void HTTPAPIServer::Run(const std::string& listenIP, uint16_t listenPort)
{
    _listenIP   = listenIP;
    _listenPort = listenPort;
    _httpServer = std::make_shared<ylg::net::HTTPServer>();
    _asyncRun   = std::async(std::launch::async, &ylg::net::HTTPServer::Run,
                             _httpServer, _listenIP, _listenPort);
}

void HTTPAPIServer::Close()
{
    if (!_httpServer)
    {
        return;
    }

    _httpServer->Close();
    _asyncRun.wait();
}
