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

#ifndef _YLG_CORE_NET_HTTP_CLIENT_H_
#define _YLG_CORE_NET_HTTP_CLIENT_H_

#include "core/net/http_context.h"

#include <curl/curl.h>

#include <system_error>

namespace ylg {
namespace net {

class HTTPClient final
{
public:
    HTTPClient(const std::string& address);
    ~HTTPClient();

public:
    HTTPClient* ResetHeader();
    HTTPClient* SetHeader(const std::string& key, const std::string& value);
    HTTPClient* SetTimeout(int seconds);

    std::error_code Put(const HTTPURI& uri, const std::string& request, int& status, std::string& response);
    std::error_code Delete(const HTTPURI& uri, const std::string& request, int& status, std::string& response);
    std::error_code Get(const HTTPURI& uri, int& status, std::string& response);
    std::error_code Post(const HTTPURI& uri, const std::string& request, int& status, std::string& response);

private:
    static std::size_t WriteData(void* data, std::size_t size, std::size_t nmemb, void* user);
    std::error_code    Execute(int& status, std::string& response);

private:
    int         _timeoutSeconds = 10;
    CURL*       _curl           = nullptr;
    std::string _address;
    Parameter   _header;
};

} // namespace net
} // namespace ylg

#endif

