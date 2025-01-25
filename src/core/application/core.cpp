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

#include "core/application/core.h"
#include "core/application/config_file.h"
#include "core/application/context.h"
#include "core/application/flag.h"

#include <system_error>

namespace ylg {
namespace app {

Core::Core()
{
    _ctx           = std::make_shared<Context>();
    _ctx->_flags   = std::make_shared<ContextFlag>();
    _ctx->_fileCfg = std::make_shared<ConfigFile>();
}

Core::~Core()
{
    Close();
}

void Core::AddCommand(const FlagInt& flag)
{
    AddFlag(&_parser, flag);
    _iFlags.push_back(flag);
}

void Core::AddCommand(const FlagString& flag)
{
    AddFlag(&_parser, flag);
    _sFlags.push_back(flag);
}

void Core::AddCommand(const FlagBool& flag)
{
    AddFlag(&_parser, flag);
    _bFlags.push_back(flag);
}

void Core::AddCommand(const FlagNoValue& flag)
{
    AddFlag(&_parser, flag);
    _nvFlags.push_back(flag);
}

std::error_code Core::Run(int argc, char* argv[], CommandHandler executor)
{
    _parser.parse_check(argc, argv);

    for (auto& flag : _iFlags)
    {
        if (!FlagExist(&_parser, flag))
        {
            continue;
        }

        flag._setted = true;
        flag._value  = GetFlagValue(&_parser, flag);

        _ctx->_flags->_iFlags[flag._fullName] = flag;
    }

    for (auto& flag : _sFlags)
    {
        if (!FlagExist(&_parser, flag))
        {
            continue;
        }

        flag._setted = true;
        flag._value  = GetFlagValue(&_parser, flag);

        _ctx->_flags->_sFlags[flag._fullName] = flag;
    }

    for (auto& flag : _bFlags)
    {
        if (!FlagExist(&_parser, flag))
        {
            continue;
        }

        flag._setted = true;
        flag._value  = GetFlagValue(&_parser, flag);

        _ctx->_flags->_bFlags[flag._fullName] = flag;
    }

    for (auto& flag : _nvFlags)
    {
        if (!FlagExist(&_parser, flag))
        {
            continue;
        }

        flag._setted = true;

        _ctx->_flags->_nvFlags[flag._fullName] = flag;
    }

    return executor(_ctx);
}

void Core::Close()
{
}

} // namespace app
} // namespace ylg

