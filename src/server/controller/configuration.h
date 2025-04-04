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

#ifndef _YLG_SERVER_CONTROLLER_CONFIG_H_
#define _YLG_SERVER_CONTROLLER_CONFIG_H_

#include "core/application/context.h"

#include <cstdint>
#include <string>

// clang-format off

#define YLG_SERVER_CONTROLLER_LOG_LEVEL_DFT                 "debug"
#define YLG_SERVER_CONTROLLER_LOG_PATH_DFT                  "/var/log/ylg/"
#define YLG_SERVER_CONTROLLER_LOG_FILE_MAX_COUNT_DFT        10
#define YLG_SERVER_CONTROLLER_LOG_FILE_MAX_FILE_SIZE_MB_DFT 100

// clang-format on

struct Configuration
{
    std::string          _name;
    std::string          _version;
    std::string          _endpointIP;
    uint16_t             _endpointPort = 0;
    std::string          _discoveryEndpoint;
    std::string          _discoveryUser;
    std::string          _discoveryPassword;
    std::string          _logPath       = YLG_SERVER_CONTROLLER_LOG_PATH_DFT;
    std::string          _logLevel      = YLG_SERVER_CONTROLLER_LOG_LEVEL_DFT;
    uint32_t             _maxFileCount  = YLG_SERVER_CONTROLLER_LOG_FILE_MAX_COUNT_DFT;
    uint32_t             _maxFileSizeMB = YLG_SERVER_CONTROLLER_LOG_FILE_MAX_FILE_SIZE_MB_DFT;
    ylg::app::ContextPtr _ctx;
};

static std::string DumpConfig(const Configuration& cfg)
{
    std::stringstream ss;
    ss << "\nname: " << cfg._name
       << "\nversion: " << cfg._version;

    ss << "\ncontroller endpoint:"
       << "\n\tip:" << cfg._endpointIP
       << "\n\tport:" << cfg._endpointPort;

    ss << "\ndiscovery:"
       << "\n\tendpoint:" << cfg._discoveryEndpoint
       << "\n\tuser:" << cfg._discoveryUser
       << "\n\tpassword:" << cfg._discoveryPassword;

    ss << "\nlog.path: " << cfg._logPath
       << "\nlog.level: " << cfg._logLevel
       << "\nlog.file-count: " << cfg._maxFileCount
       << "\nlog.file-sizeMB: " << cfg._maxFileSizeMB;

    return ss.str();
}

using ConfigurationPtr = std::shared_ptr<Configuration>;

#endif

