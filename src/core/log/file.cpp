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

#include "core/log/file.h"

#include <spdlog/common.h>
#include <spdlog/details/os.h>

#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <tuple>

namespace ylg {
namespace log {

File::File(const spdlog::file_event_handlers& inHandlers)
    : _handlers(inHandlers) {}

File::~File()
{
    Close();
}

std::tuple<spdlog::filename_t, spdlog::filename_t> File::SplitByExt(const spdlog::filename_t& fileName)
{
    std::string::size_type extPos = fileName.rfind('.');

    // return whole path and empty extension
    if (extPos == spdlog::filename_t::npos || extPos == 0 || extPos == fileName.size() - 1)
    {
        return std::make_tuple(fileName, spdlog::filename_t());
    }

    // case like /var/log.d/logfile or /var/log/.hiddenlogfile
    auto folderIdx = fileName.find_last_of(spdlog::details::os::folder_seps_filename);
    if (folderIdx != spdlog::filename_t::npos && folderIdx >= extPos - 1)
    {
        return std::make_tuple(fileName, spdlog::filename_t());
    }

    return std::make_tuple(fileName.substr(0, extPos), fileName.substr(extPos));
}

void File::Open(const spdlog::filename_t& fileName, bool truncate)
{
    Close();
    _name = fileName;

    const char* mode      = SPDLOG_FILENAME_T("ab");
    const char* truncMode = SPDLOG_FILENAME_T("wb");

    if (_handlers.before_open)
    {
        _handlers.before_open(_name);
    }

    for (int idx = 0; idx < _openRetries; ++idx)
    {
        spdlog::details::os::create_dir(spdlog::details::os::dir_name(fileName));
        if (truncate)
        {
            std::FILE* tmp = nullptr;
            if (spdlog::details::os::fopen_s(&tmp, _name, truncMode))
            {
                continue;
            }

            std::fclose(tmp);
        }

        if (!spdlog::details::os::fopen_s(&_fd, _name, mode))
        {
            if (_handlers.after_open)
            {
                _handlers.after_open(_name, _fd);
            }

            return;
        }

        spdlog::details::os::sleep_for_millis(_openInterval);
    }

    spdlog::throw_spdlog_ex("failed to open the log file: " + spdlog::details::os::filename_to_str(_name), errno);
}

void File::Reopen(bool truncate)
{
    if (_name.empty())
    {
        spdlog::throw_spdlog_ex("failed to reopen the log file: " + spdlog::details::os::filename_to_str(_name));
    }

    Open(_name, truncate);
}

bool File::Flush()
{
    if (std::fflush(_fd))
    {
        Reopen(false);
        return false;
    }

    return true;
}

void File::Close()
{
    if (!_fd)
    {
        return;
    }

    if (_handlers.before_close)
    {
        _handlers.before_close(_name, _fd);
    }

    std::fclose(_fd);
    _fd = nullptr;

    if (_handlers.after_close)
    {
        _handlers.after_close(_name);
    }
}

bool File::Write(const spdlog::memory_buf_t& buffer)
{
    std::size_t size = buffer.size();
    const char* data = buffer.data();

    if (std::fwrite(data, 1, size, _fd) != size)
    {
        Reopen(false);
        return false;
    }

    return true;
}

std::size_t File::Size()
{
    if (!_fd)
    {
        return 0;
    }

    return spdlog::details::os::filesize(_fd);
}

const spdlog::filename_t& File::Name() const
{
    return _name;
}

} // namespace log
} // namespace ylg
