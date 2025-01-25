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

#include "core/log/log.h"
#include "core/assist/file.h"
#include "core/assist/macro.h"
#include "core/assist/string.h"
#include "core/assist/time.h"
#include "core/log/error.h"
#include "core/log/file_sink.h"

#include <spdlog/async_logger.h>
#include <spdlog/common.h>
#include <spdlog/details/thread_pool.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <cstdio>
#include <memory>
#include <system_error>

namespace ylg {
namespace log {

Logger::Logger()
{
    _isOpen.store(false);
}

Logger::~Logger()
{
    _isOpen.store(false);

    if (_stdOut)
    {
        fclose(_stdOut);
        _stdOut = nullptr;
    }

    if (_stdErr)
    {
        fclose(_stdErr);
        _stdErr = nullptr;
    }
}

Logger& Logger::Instance()
{
    static Logger inst;
    return inst;
}

std::error_code Logger::Init(const std::string& name, const LogConfig& cfg)
{

    BEGIN_TRY

    RedirectSTD(name, cfg);

    std::vector<spdlog::sink_ptr> sinks;

    auto level = Parse(cfg._level);

    if (level <= spdlog::level::err)
    {
        auto errSink = std::make_shared<FileSink>(cfg._path, name + ".error",
                                                  cfg._fileSizeMB * 1024 * 1024, cfg._fileCount, true);

        errSink->set_level(spdlog::level::err);
        sinks.push_back(errSink);
    }

    if (level <= spdlog::level::warn)
    {
        auto warnSink = std::make_shared<FileSink>(cfg._path, name + ".warn",
                                                   cfg._fileSizeMB * 1024 * 1024, cfg._fileCount, true);

        warnSink->set_level(spdlog::level::warn);
        sinks.push_back(warnSink);
    }

    if (level <= spdlog::level::info)
    {
        auto infoSink = std::make_shared<FileSink>(cfg._path, name + ".info",
                                                   cfg._fileSizeMB * 1024 * 1024, cfg._fileCount, true);

        infoSink->set_level(spdlog::level::info);
        sinks.push_back(infoSink);
    }

    if (level <= spdlog::level::debug)
    {
        auto debugSink = std::make_shared<FileSink>(cfg._path, name + ".debug",
                                                    cfg._fileSizeMB * 1024 * 1024, cfg._fileCount, true);

        debugSink->set_level(spdlog::level::debug);
        sinks.push_back(debugSink);
    }

    _threadPoolPtr = std::make_shared<spdlog::details::thread_pool>(cfg._queueSize, cfg._threadCount);
    _asyncLogger   = std::make_shared<spdlog::async_logger>(name, sinks.begin(), sinks.end(),
                                                            _threadPoolPtr, spdlog::async_overflow_policy::overrun_oldest);

    _asyncLogger->set_level(level);
    _asyncLogger->set_pattern("[%L%m%d %H:%M%S.%f %P-%t %s:%#] %v");

    spdlog::register_logger(_asyncLogger);
    spdlog::flush_every(std::chrono::milliseconds(cfg._flushMS));

    END_TRY_BEGIN_CATCH(spdlog::spdlog_ex, ex)

    LOG_STD("can not init spd log. errmsg({})", ex.what());
    return MakeError(ErrorCode::Error);

    END_CATCH_AND_BEGIN_CATCH_ALL

    LOG_STD("can not init spd log. errmsg({})", "unknown exception");
    return MakeError(ErrorCode::Error);

    END_CATCH_ALL

    _isOpen.store(true);
    return MakeSuccess();
}

void Logger::Close()
{
    _isOpen.store(false);

    assist::Sleep(3);

    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> g) { g->flush(); });

    spdlog::shutdown();
}

bool Logger::IsOpen()
{
    return _isOpen;
}

std::shared_ptr<spdlog::async_logger> Logger::AsyncLogger()
{
    return _asyncLogger;
}

spdlog::level::level_enum Logger::Parse(const std::string& level)
{
    if (assist::Comapre(level, LEVEL_ERROR, true) == 0)
    {
        LOG_STD("set log level(%s)", level.c_str());
        return spdlog::level::err;
    }

    if (assist::Comapre(level, LEVEL_WARN, true) == 0)
    {
        LOG_STD("set log level(%s)", level.c_str());
        return spdlog::level::warn;
    }

    if (assist::Comapre(level, LEVEL_INFO, true) == 0)
    {
        LOG_STD("set log level(%s)", level.c_str());
        return spdlog::level::info;
    }

    if (assist::Comapre(level, LEVEL_DEBUG) == 0)
    {
        LOG_STD("set log level(%s)", level.c_str());
        return spdlog::level::debug;
    }

    LOG_STD("unknown log level(%s), use default(info)", level.c_str());
    return spdlog::level::info;
}

bool Logger::RedirectSTD(const std::string& name, const LogConfig& cfg)
{
    if (!assist::FileExists(cfg._path))
    {
        return false;
    }

    auto logFile = assist::JoinPath({cfg._path, name + ".std"});

    if (assist::FileExists(logFile))
    {
        auto ec = assist::DeleteFile(logFile + ".bak");
        if (!IsSuccess(ec))
        {
            // ignore error
        }

        ec = assist::RenameFile(logFile, logFile + ".bak");
        if (!IsSuccess(ec))
        {
            // ignore error
        }
    }

    _stdOut = std::freopen(logFile.c_str(), "w+", stdout);
    _stdErr = std::freopen(logFile.c_str(), "w+", stderr);

    if (!_stdOut || !_stdErr)
    {
        return false;
    }

    return true;
}

} // namespace log
} // namespace ylg

