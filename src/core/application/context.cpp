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

#include "core/application/context.h"
#include "core/assist/string.h"
#include "core/error/error.h"

#include <cstdint>
#include <string>

namespace ylg {
namespace app {

template <>
FlagInt Context::GetFlagValue<FlagInt>(const std::string& name)
{
    auto iter = _flags->_iFlags.find(name);
    if (iter != _flags->_iFlags.end())
    {
        return iter->second;
    }

    return FlagInt();
}

template <>
FlagBool Context::GetFlagValue<FlagBool>(const std::string& name)
{
    auto iter = _flags->_bFlags.find(name);
    if (iter != _flags->_bFlags.end())
    {
        return iter->second;
    }

    return FlagBool();
}

template <>
FlagString Context::GetFlagValue<FlagString>(const std::string& name)
{
    auto iter = _flags->_sFlags.find(name);
    if (iter != _flags->_sFlags.end())
    {
        return iter->second;
    }

    return FlagString();
}

template <>
FlagNoValue Context::GetFlagValue<FlagNoValue>(const std::string& name)
{
    auto iter = _flags->_nvFlags.find(name);
    if (iter != _flags->_nvFlags.end())
    {
        return iter->second;
    }

    return FlagNoValue();
}

bool Context::FlagExist(const std::string& name)
{
    auto iter = _flags->_iFlags.find(name);
    if (iter != _flags->_iFlags.end())
    {
        return true;
    }

    auto siter = _flags->_sFlags.find(name);
    if (siter != _flags->_sFlags.end())
    {
        return true;
    }

    auto biter = _flags->_bFlags.find(name);
    if (biter != _flags->_bFlags.end())
    {
        return true;
    }

    auto nviter = _flags->_nvFlags.find(name);
    if (nviter != _flags->_nvFlags.end())
    {
        return true;
    }

    return false;
}

template <>
bool Context::GetFileConfig<bool>(const std::string& name, bool defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return assist::ToBool(val);
}

template <>
float Context::GetFileConfig<float>(const std::string& name, float defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stof(val);
}

template <>
double Context::GetFileConfig<double>(const std::string& name, double defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stod(val);
}

template <>
std::string Context::GetFileConfig<std::string>(const std::string& name, std::string defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return val;
}

template <>
int Context::GetFileConfig<int>(const std::string& name, int defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoi(val);
}

template <>
int64_t Context::GetFileConfig<int64_t>(const std::string& name, int64_t defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoll(val);
}

template <>
uint32_t Context::GetFileConfig<uint32_t>(const std::string& name, uint32_t defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoul(val);
}

template <>
uint64_t Context::GetFileConfig<uint64_t>(const std::string& name, uint64_t defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoull(val);
}

template <>
int16_t Context::GetFileConfig<int16_t>(const std::string& name, int16_t defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoi(val);
}

template <>
uint16_t Context::GetFileConfig<uint16_t>(const std::string& name, uint16_t defaultValue)
{
    if (!_fileCfg->Exist(name))
    {
        return defaultValue;
    }

    auto val = _fileCfg->Get(name);
    return std::stoi(val);
}

bool Context::FileConfigExist(const std::string& name)
{
    return _fileCfg->Exist(name);
}

std::error_code Context::LoadConfig(const std::string& fileName)
{
    auto ec = _fileCfg->Load(fileName);

    if (!error::IsSuccess(ec))
    {
        return ec;
    }

    return ec;
}

} // namespace app
} // namespace ylg

