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

#ifndef _YLG_CORE_LOG_FILE_H_
#define _YLG_CORE_LOG_FILE_H_

#include <spdlog/common.h>

#include <cstdint>
#include <cstdio>

namespace ylg {
namespace log {

class File final
{
public:
    File() = default;
    File(const spdlog::file_event_handlers& inHandlers);
    File(const File&)            = delete;
    File& operator=(const File&) = delete;
    ~File();

public:
    static std::tuple<spdlog::filename_t, spdlog::filename_t> SplitByExt(const spdlog::filename_t& fileName);

public:
    void                      Open(const spdlog::filename_t& fileName, bool truncate = false);
    void                      Reopen(bool truncate);
    bool                      Flush();
    void                      Close();
    bool                      Write(const spdlog::memory_buf_t& buffer);
    std::size_t               Size();
    const spdlog::filename_t& Name() const;

private:
    uint32_t                    _openRetries  = 5;
    uint32_t                    _openInterval = 10;
    std::FILE*                  _fd           = nullptr;
    spdlog::filename_t          _name;
    spdlog::file_event_handlers _handlers;
};

} // namespace log
} // namespace ylg

#endif
