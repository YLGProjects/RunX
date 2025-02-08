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

#include "core/application/discovery.h"
#include "core/error/error.h"

namespace ylg {
namespace app {

std::error_code Discovery::Watch(const std::string& key, CallbackFunctor callback)
{
    return error::ErrorCode::Success;
}

std::error_code Discovery::GetList(const std::string& key, std::vector<std::string>& elements)
{
    return error::ErrorCode::Success;
}

std::error_code Discovery::GetValue(const std::string& key, std::string& value)
{
    return error::ErrorCode::Success;
}

std::error_code Discovery::Start(const std::string& endpoints, std::string* errMsg)
{
    return error::ErrorCode::Success;
}

void Stop();

} // namespace app
} // namespace ylg

