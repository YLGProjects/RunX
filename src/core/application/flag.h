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

#ifndef _YLG_CORE_APP_FLAG_H_
#define _YLG_CORE_APP_FLAG_H_

#include "third-party/cmdline/cmdline.h"

#include <functional>
#include <string>
#include <vector>

namespace ylg {
namespace app {

using FlagHandler = std::function<std::error_code(void* ctx)>;

struct FlagObject
{
};

template <typename T>
struct Flag
{
    std::string    _fullName;
    char           _shortName;
    std::string    _description;
    FlagHandler    _handler;
    bool           _required = false;
    T              _value    = T();
    std::vector<T> _range;
    std::vector<T> _oneof;
    bool           _setted = false;
};

struct NoValue
{
};

template <typename T>
void AddFlag(cmdline::parser* parser, const Flag<T>& flag)
{
    parser->add<T>(flag._fullName, flag._shortName, flag._description, flag._required, flag._value);
}

template <typename T>
T GetFlagValue(cmdline::parser* parser, const Flag<T>& flag)
{
    return parser->get<T>(flag._fullName);
}

template <typename T>
bool FlagExist(cmdline::parser* parser, const Flag<T>& flag)
{
    return parser->exist(flag._fullName);
}

using FlagInt     = Flag<int>;
using FlagBool    = Flag<bool>;
using FlagNoValue = Flag<NoValue>;
using FlagString  = Flag<std::string>;

template <>
void AddFlag<NoValue>(cmdline::parser* parser, const Flag<NoValue>& flag);

} // namespace app
} // namespace ylg

#endif
