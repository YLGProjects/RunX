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

#include "core/application/config_file.h"
#include "core/assist/macro.h"
#include "core/error/error.h"
#include "core/log/log.h"

#include <cstddef>
#include <iostream>
#include <string>

#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/node/parse.h>

namespace ylg {
namespace app {

std::error_code ConfigFile::Load(const std::string& filePath)
{
    BEGIN_TRY

    _fileName   = filePath;
    auto config = YAML::LoadFile(filePath);

    for (const auto& entry : config)
    {
        auto key = entry.first.as<std::string>();
        Traverse(entry.second, key);
    }

    END_TRY_BEGIN_CATCH(YAML::ParserException, ex)

    LOG_ERROR("failed to parse the yaml file. file({}), errmsg({})", filePath, ex.what());
    return error::ErrorCode::ParseConfigFailure;

    END_TRY_BEGIN_CATCH(YAML::BadFile, ex)

    LOG_ERROR("failed to parse the yaml file. file({}), errmsg({})", filePath, ex.what());
    return error::ErrorCode::ParseConfigFailure;

    END_CATCH

    return error::ErrorCode::Success;
}

void ConfigFile::PrintVars()
{
    for (const auto& iter : _keyValues)
    {
        LOG_STD("key(%s), value(%s)", iter.first.c_str(), iter.second.c_str());
    }
}

std::string ConfigFile::Get(const std::string& key)
{
    auto iter = _keyValues.find(key);

    if (iter != _keyValues.end())
    {
        return iter->second;
    }

    return "";
}

bool ConfigFile::Exist(const std::string& key)
{
    auto iter = _keyValues.find(key);
    if (iter != _keyValues.end())
    {
        return true;
    }
    return false;
}

void ConfigFile::Traverse(const YAML::Node& node, const std::string& key)
{
    if (node.IsMap())
    {
        for (const auto& entry : node)
        {
            auto keyName    = entry.first.as<std::string>();
            auto newKeyName = key.empty() ? key : key + "." + keyName;
            Traverse(entry.second, newKeyName);
        }
    }
    else if (node.IsSequence())
    {
        for (std::size_t idx = 0; idx < node.size(); ++idx)
        {
            auto keyName = key + ".[" + std::to_string(idx) + "]";
            Traverse(node[idx], keyName);
        }
    }
    else if (node.IsScalar())
    {
        _keyValues[key] = node.as<std::string>();
    }
    else if (node.IsNull())
    {
        _keyValues[key] = "";
    }
    else
    {
        std::cout << "unknown key: -- " << key << std::endl;
        _keyValues[key] = node.as<std::string>();
    }
}

} // namespace app
} // namespace ylg

