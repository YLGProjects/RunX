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

#include "core/assist/memory.h"
#include "core/error/error.h"
#include "core/log/log.h"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include <fcntl.h>

namespace ylg {
namespace assist {

bool IsFile(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    return std::filesystem::is_regular_file(name);
}

bool IsDirectory(const std::string& name)
{
    if (name.empty())
    {
        return false;
    }

    return std::filesystem::is_directory(name);
}

bool FileExists(const std::string& fileName)
{
    if (fileName.empty())
    {
        return false;
    }

    return std::filesystem::exists(fileName);
}

int64_t FileSize(const std::string& fileName)
{
    if (fileName.empty())
    {
        return 0;
    }

    std::uintmax_t bytes = 0;

    try
    {
        bytes = std::filesystem::file_size(fileName);
    }
    catch (std::filesystem::filesystem_error& e)
    {
        return -1;
    }

    return bytes / 1024 / 1024; // MB
}

std::error_code ReadFullFile(const std::string& fileName, std::string& content)
{
    content = "";

    if (fileName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    if (!FileExists(fileName))
    {
        return error::ErrorCode::FILE_EXCEPTION;
    }

    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return error::ErrorCode::FILE_EXCEPTION;
    }

    std::string line;
    while (std::getline(file, line))
    {
        content.append(line);
    }

    file.close();

    return error::ErrorCode::SUCCESS;
}

std::error_code DeleteFile(const std::string& fileName)
{
    if (fileName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    bool isOK = false;

    try
    {
        isOK = std::filesystem::remove(fileName);
    }
    catch (std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("can not delete the file({}). errmsg({})", fileName, e.what());
        return error::ErrorCode::FILE_EXCEPTION;
    }

    return isOK ? error::ErrorCode::SUCCESS : error::ErrorCode::FILE_EXCEPTION;
}

std::error_code DeleteDirectory(const std::string& fileName)
{
    if (fileName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    std::uintmax_t removedNum = 0;

    try
    {
        removedNum = std::filesystem::remove_all(fileName);
    }
    catch (std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("can not delete the file({}). errmsg({})", fileName, e.what());
        return error::ErrorCode::FILE_EXCEPTION;
    }

    return removedNum > 0 ? error::ErrorCode::SUCCESS : error::ErrorCode::FILE_EXCEPTION;
}

std::error_code RenameFile(const std::string& oldName, const std::string& newName)
{
    if (oldName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    if (newName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    try
    {
        std::filesystem::rename(oldName, newName);
    }
    catch (std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("can not rename the file({}). new file({}), errmsg({})", oldName, newName, e.what());
        return error::ErrorCode::FILE_EXCEPTION;
    }

    return error::ErrorCode::FILE_EXCEPTION;
}

std::error_code SetFileUser(const std::string& fileName, const std::string& userName)
{
    if (fileName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    if (userName.empty())
    {
        return error::ErrorCode::SYSTEM_INVALID_USER;
    }

    int uid = 0;
    int gid = 0;

    return error::ErrorCode::SUCCESS;
}

std::error_code SetFilePermission(const std::string& fileName, int mode)
{
    return error::ErrorCode::SUCCESS;
}

std::error_code ListFile(const std::string& dirName, std::vector<std::string>& files, bool recursive)
{
    if (dirName.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    try
    {
        for (auto& entry : std::filesystem::directory_iterator(dirName))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path());
                continue;
            }

            if (entry.is_directory() && recursive)
            {
                auto ec = ListFile(entry.path(), files, recursive);
                if (!error::IsSuccess(ec))
                {
                    return ec;
                }
            }
        }
    }
    catch (std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("can not list file. dir({}), errmsg({}))", dirName, e.what());
        return error::ErrorCode::FILE_EXCEPTION;
    }

    return error::ErrorCode::SUCCESS;
}

std::error_code MakeDirectory(const std::string& dirPath)
{
    if (dirPath.empty())
    {
        return error::ErrorCode::INVALID_PARAMETER;
    }

    try
    {
        std::filesystem::create_directories(dirPath);
    }
    catch (std::filesystem::filesystem_error& e)
    {
        LOG_ERROR("can not make the directory. dir({}), errmsg({}))", dirPath, e.what());
        return error::ErrorCode::FILE_EXCEPTION;
    }

    return error::ErrorCode::SUCCESS;
}

std::string JoinPath(const std::vector<std::string>& paths)
{
    std::string result;

    for (auto iter = paths.begin(); iter != paths.end(); ++iter)
    {
        result.append("/");
        result.append(*iter);
    }

    return result;
}

std::string JoinPath(const std::string& prefix, const std::vector<std::string>& paths)
{
    std::string result(prefix);

    for (auto iter = paths.begin(); iter != paths.end(); ++iter)
    {
        if (!result.empty() && result.back() != '/')
        {
            result.append("/");
        }

        result.append(*iter);
    }

    return result;
}

std::error_code LockFile(int fileFD)
{
    struct flock fl;
    SetMemory(&fl, 0, sizeof(struct flock));

    fl.l_type   = F_WRLCK;
    fl.l_whence = SEEK_SET;

    if (fcntl(fileFD, F_SETLK, &fl) == -1)
    {
        LOG_ERROR("can not lock file, errmsg({})", error::ToString(errno));
        return error::ErrorCode::ERROR;
    }

    return error::ErrorCode::SUCCESS;
}

std::error_code UnlockFile(int fileFD)
{
    struct flock fl;
    SetMemory(&fl, 0, sizeof(struct flock));

    fl.l_type   = F_UNLCK;
    fl.l_whence = SEEK_SET;

    if (fcntl(fileFD, F_SETLK, &fl) == -1)
    {
        LOG_ERROR("can not unlock file, errmsg({})", error::ToString(errno));
        return error::ErrorCode::ERROR;
    }

    return error::ErrorCode::SUCCESS;
}

} // namespace assist
} // namespace ylg

