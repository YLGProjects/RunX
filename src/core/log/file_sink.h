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

#ifndef _YLG_CORE_LOG_FILE_SINK_H_
#define _YLG_CORE_LOG_FILE_SINK_H_

#include "core/log/file.h"

#include <spdlog/common.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/sinks/base_sink.h>

#include <cstddef>
#include <mutex>

namespace ylg {
namespace log {

class FileSink final : public spdlog::sinks::base_sink<std::mutex>
{
public:
    FileSink(const std::string& path, spdlog::filename_t fileName, std::size_t max,
             std::size_t maxCount, bool rotateOnOpen = false,
             const spdlog::file_event_handlers& handlers = {});

public:
    /**
     * @brief return the log _file name
     *
     * @return spdlog::filename_t
     */
    spdlog::filename_t FileName();

protected:
    /**
     * @brief sink_it_ override the sink operation
     *
     * @param message the log message
     */
    void sink_it_(const spdlog::details::log_msg& message) override;

    /**
     * @brief flush_ override the sink operaion
     *
     */
    void flush_() override;

private:
    /**
     * @brief Rotate rotate the log _file base on the rule(max size and _file count)
     *
     */
    void Rotate();

    /**
     * @brief RenameFile rename the srcName to dstName, delete the dstName if exists
     *
     * @param srcName the source _file name
     * @param dstName the dest _file name
     * @return true success
     * @return false failure
     */
    bool RenameFile(const spdlog::filename_t& srcName, const spdlog::filename_t& dstName);

private:
    std::string        _basePath;
    spdlog::filename_t _baseFileName;
    File               _file;
    std::size_t        _maxSize      = 0;
    std::size_t        _maxFileCount = 0;
    std::size_t        _currentSize  = 0;
};

} // namespace log
} // namespace ylg

#endif
