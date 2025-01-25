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

#ifndef _YLG_CORE_APP_CONFIG_FILE_H_
#define _YLG_CORE_APP_CONFIG_FILE_H_

#include <map>
#include <memory>
#include <string>
#include <system_error>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>

namespace ylg {
namespace app {

class ConfigFile final
{
public:
    std::error_code Load(const std::string& filePath);
    void            PrintVars();

public:
    std::string Get(const std::string& key);
    bool Exist(const std::string& key);

private:
    void Traverse(const YAML::Node& node, const std::string& key);

private:
    std::string                        _fileName;
    std::map<std::string, std::string> _keyValues;
};

using ConfigFilePtr = std::shared_ptr<ConfigFile>;

} // namespace app
} // namespace ylg

#endif
