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

#ifndef _YLG_CORE_APP_CONTEXT_H_
#define _YLG_CORE_APP_CONTEXT_H_

#include "core/application/config_file.h"
#include "core/application/flag.h"
#include "core/container/safe_map.h"

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace ylg {
namespace app {

struct ContextFlag
{
    std::map<std::string, FlagInt>     _iFlags;
    std::map<std::string, FlagString>  _sFlags;
    std::map<std::string, FlagBool>    _bFlags;
    std::map<std::string, FlagNoValue> _nvFlags;
};

using CacheName      = std::string;
using ContextFlagPtr = std::shared_ptr<ContextFlag>;

class Context final
{
public:
    template <typename T>
    std::error_code Save(const CacheName& name, T* data);

    template <typename T>
    T* Get(const CacheName& name);

    template <typename T>
    T GetFlagValue(const std::string& name) { return T{}; };

    bool FlagExist(const std::string& name);

    template <typename T>
    T GetFileConfig(const std::string& name, T defaultValue = T{});

    bool FileConfigExist(const std::string& name);

    std::error_code LoadConfig(const std::string& fileName);

private:
    friend class Core;
    container::SafeMap<std::string, void*> _caches;
    ContextFlagPtr                         _flags;
    ConfigFilePtr                          _fileCfg;
};

using ContextPtr = std::shared_ptr<Context>;

template <>
FlagInt Context::GetFlagValue<FlagInt>(const std::string& name);

template <>
FlagBool Context::GetFlagValue<FlagBool>(const std::string& name);

template <>
FlagString Context::GetFlagValue<FlagString>(const std::string& name);

template <>
FlagNoValue Context::GetFlagValue<FlagNoValue>(const std::string& name);

template <>
bool Context::GetFileConfig<bool>(const std::string& name, bool defaultValue);

template <>
float Context::GetFileConfig<float>(const std::string& name, float defaultValue);

template <>
double Context::GetFileConfig<double>(const std::string& name, double defaultValue);

template <>
std::string Context::GetFileConfig<std::string>(const std::string& name, std::string defaultValue);

template <>
int Context::GetFileConfig<int>(const std::string& name, int defaultValue);

template <>
int64_t Context::GetFileConfig<int64_t>(const std::string& name, int64_t defaultValue);

template <>
uint32_t Context::GetFileConfig<uint32_t>(const std::string& name, uint32_t defaultValue);

template <>
uint64_t Context::GetFileConfig<uint64_t>(const std::string& name, uint64_t defaultValue);

template <>
int16_t Context::GetFileConfig<int16_t>(const std::string& name, int16_t defaultValue);

template <>
uint16_t Context::GetFileConfig<uint16_t>(const std::string& name, uint16_t defaultValue);

} // namespace app
} // namespace ylg

#endif
