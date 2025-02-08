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

#include "core/assist/user.h"
#include "core/assist/memory.h"
#include "core/error/error.h"
#include "core/log/log.h"

#include <pwd.h>
#include <unistd.h>

namespace ylg {
namespace assist {

bool UserExists(const std::string& userName)
{
    if (userName.empty())
    {
        return false;
    }

    struct passwd  pwd;
    struct passwd* res = nullptr;
    char           buffer[1024];

    ZeroMemory(buffer, sizeof(buffer));

    return getpwnam_r(userName.c_str(), &pwd, buffer, sizeof(buffer), &res) == 0 && res != nullptr;
}

std::error_code GetUserUidGid(const std::string& userName, int& uid, int& gid)
{
    struct passwd  pwd;
    struct passwd* res = nullptr;
    char           buffer[1024];

    ZeroMemory(buffer, sizeof(buffer));

    auto isOK = getpwnam_r(userName.c_str(), &pwd, buffer, sizeof(buffer), &res) && res != nullptr;
    if (!isOK)
    {
        LOG_ERROR("can not get uid and gid. errmsg({})", error::ToString(errno));
        return error::ErrorCode::Error;
    }

    uid = res->pw_uid;
    gid = res->pw_gid;

    return error::ErrorCode::Success;
}

std::error_code GetUserUidGid(const std::string& userName, int& uid, int& gid, std::string& homeDirectory, std::string& shell)
{
    struct passwd  pwd;
    struct passwd* res = nullptr;
    char           buffer[1024];

    ZeroMemory(buffer, sizeof(buffer));

    auto isOK = getpwnam_r(userName.c_str(), &pwd, buffer, sizeof(buffer), &res) && res != nullptr;
    if (!isOK)
    {
        LOG_ERROR("can not get uid and gid. errmsg({})", error::ToString(errno));
        return error::ErrorCode::Error;
    }

    uid           = res->pw_uid;
    gid           = res->pw_gid;
    shell         = res->pw_shell;
    homeDirectory = res->pw_dir;

    return error::ErrorCode::Success;
}

std::error_code SetUserUidGid(int uid, int gid)
{
    if (setregid(gid, gid))
    {
        LOG_ERROR("can not set gid. errmsg({})", error::ToString(errno));
        return error::ErrorCode::Error;
    }

    if (setreuid(uid, uid))
    {
        LOG_ERROR("can not get uid. errmsg({})", error::ToString(errno));
        return error::ErrorCode::Error;
    }

    return error::ErrorCode::Success;
}

} // namespace assist
} // namespace ylg

