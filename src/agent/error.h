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

#ifndef _YLG_AGENT_ERROR_H_
#define _YLG_AGENT_ERROR_H_

#include <system_error>

enum class ErrorCode
{
    Unknown = -2,
    Error   = -1,
    Success = 0,
    MaxValue,

};

class ErrorCodeCategory final : public std::error_category
{
public:
    static ErrorCodeCategory& Instance();

public:
    const char* name() const noexcept override;
    std::string message(int code) const override;
};

/**
 * @brief ConvertToCode convert code to enum value
 *
 * @param code int value
 * @return Code enum value
 */
ErrorCode ConvertToCode(int code);

/**
 * @brief MakeError make ylg error code
 *
 * @param ec error code value
 * @return std::error_code custom error msg
 */
std::error_code MakeError(ErrorCode ec);
std::error_code MakeSuccess();

/**
 * @brief check ec is Code::Success
 *
 * @param ec the target ec
 * @return true is success
 * @return false is failed
 */
bool IsSuccess(const std::error_code& ec);

/**
 * @brief transfer error code to string
 *
 * @param ec error code
 * @return const char* error message
 */
std::string ToString(int ec);

#endif
