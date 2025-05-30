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

#include "internal/error.h"
#include "core/error/error.h"

namespace ylg {
namespace internal {

ErrorCodeCategory& ErrorCodeCategory::Instance()
{
    static ErrorCodeCategory instance;
    return instance;
}

const char* ErrorCodeCategory::name() const noexcept
{
    return "ylg-internal-error";
}

std::string ErrorCodeCategory::message(int code) const
{
    if (code < (int32_t)ylg::error::ErrorCode::MAX)
    {
        return ylg::error::ErrorCodeCategory::Instance().message(code);
    }

    std::string errMsg;
    switch (static_cast<ErrorCode>(code))
    {
    default:
        errMsg = std::to_string(code) + ": unknown error code";
    }
    return errMsg;
}

std::error_code make_error_code(ErrorCode e)
{
    return {static_cast<int>(e), ErrorCodeCategory::Instance()};
}

bool IsSuccess(const std::error_code& ec)
{
    if (ec.value() == (int)ErrorCode::SUCCESS)
    {
        return true;
    }

    return false;
}

std::string ToString(int ec)
{
    return std::system_category().message(ec);
}

} // namespace internal
} // namespace ylg

namespace std {
} // namespace std
