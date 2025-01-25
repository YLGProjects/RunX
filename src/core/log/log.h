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

#ifndef _YLG_CORE_LOG_H_
#define _YLG_CORE_LOG_H_

#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/common.h>
#include <spdlog/details/thread_pool.h>
#include <spdlog/spdlog.h>

#include <cstdio>
#include <memory>
#include <string>

namespace ylg {
namespace log {

// clang-format off

#define LEVEL_DEBUG "debug"
#define LEVEL_INFO  "info"
#define LEVEL_WARN  "warn"
#define LEVEL_ERROR "error"

// clang-format on

struct LogConfig
{
    std::string _level       = LEVEL_INFO;
    std::string _path        = "log";
    int         _fileSizeMB  = 100;
    int         _fileCount   = 5;
    int         _flushMS     = 100;
    std::string _pattern     = "[%L%m%d %H:%M:%S.%f %P-%t %s:%#] %v";
    int         _threadCount = 1;
    int         _queueSize   = 36480;
};

class Logger final
{
public:
    Logger();
    ~Logger();

public:
    static Logger& Instance();

public:
    std::error_code                       Init(const std::string& name, const LogConfig& cfg);
    void                                  Close();
    bool                                  IsOpen();
    std::shared_ptr<spdlog::async_logger> AsyncLogger();

private:
    spdlog::level::level_enum Parse(const std::string& level);
    bool                      RedirectSTD(const std::string& name, const LogConfig& cfg);

private:
    std::shared_ptr<spdlog::details::thread_pool> _threadPoolPtr;
    std::shared_ptr<spdlog::async_logger>         _asyncLogger;
    std::FILE*                                    _stdOut = nullptr;
    std::FILE*                                    _stdErr = nullptr;
    std::atomic_bool                              _isOpen = false;
};

} // namespace log
} // namespace ylg

#define LOG_STD_FORMAT(fileName, lineNum, funcName, fmt, ...) \
    do {                                                      \
        std::string format;                                   \
        format.append(fileName);                              \
        format.append(",");                                   \
        format.append(std::to_string(lineNum));               \
        format.append(",");                                   \
        format.append(funcName);                              \
        format.append(" ");                                   \
        format.append(fmt);                                   \
        format.append("\n");                                  \
        std::fprintf(stdout, format.c_str(), ##__VA_ARGS__);  \
    } while (0)

#define LOG_FORMAT(level, fileName, lineNum, funcName, fmt, ...)                                           \
    do {                                                                                                   \
        auto& inst = ylg::log::Logger::Instance();                                                         \
        if (inst.IsOpen())                                                                                 \
        {                                                                                                  \
            auto logger = inst.AsyncLogger();                                                              \
            if (logger && logger->should_log(level))                                                       \
            {                                                                                              \
                logger->log(spdlog::source_loc{fileName, lineNum, funcName}, level, (fmt), ##__VA_ARGS__); \
            }                                                                                              \
        }                                                                                                  \
    } while (0)

#define LOG_FATAL(fmt, ...)                                                                                             \
    do {                                                                                                                \
        auto& inst   = ylg::log::Logger::Instance();                                                                    \
        auto  logger = inst.AsyncLogger();                                                                              \
        logger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, (fmt), ##__VA_ARGS__); \
        inst.Close();                                                                                                   \
        _exit(1);                                                                                                       \
    } while (0)

#define LOG_STD(fmt, ...) \
    LOG_STD_FORMAT(__FILE__, __LINE__, SPDLOG_FUNCTION, (fmt), ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...) \
    LOG_FORMAT(spdlog::level::debug, __FILE__, __LINE__, SPDLOG_FUNCTION, (fmt), ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
    LOG_FORMAT(spdlog::level::info, __FILE__, __LINE__, SPDLOG_FUNCTION, (fmt), ##__VA_ARGS__)

#define LOG_WARN(fmt, ...) \
    LOG_FORMAT(spdlog::level::warn, __FILE__, __LINE__, SPDLOG_FUNCTION, (fmt), ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    LOG_FORMAT(spdlog::level::err, __FILE__, __LINE__, SPDLOG_FUNCTION, (fmt), ##__VA_ARGS__)

#endif
