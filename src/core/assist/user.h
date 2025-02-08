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

#ifndef _YLG_CORE_ASSIST_USER_H_
#define _YLG_CORE_ASSIST_USER_H_

#include "core/error/error.h"

#include <string>

namespace ylg {
namespace assist {

/**
 * @brief UserExists check the user if it's exists
 *
 * @param userName the user name
 * @return true the user is valid
 * @return false the user is invalid
 */
bool UserExists(const std::string& userName);

/**
 * @brief GetUserUidGid get the user's uid and gid
 *
 * @param userName the user name
 * @param uid the user's uid
 * @param gid the user's gid
 * @return std::error_code Success it's success, other value is error
 */
std::error_code GetUserUidGid(const std::string& userName, int& uid, int& gid);

/**
 * @brief GetUserUidGid get the user's information
 *
 * @param userName the user name
 * @param uid the user ID
 * @param gid the user group ID
 * @param homeDirectory the user home directory
 * @param shell the user shell program
 * @return std::error_code Success it's success, other value is error
 */
std::error_code GetUserUidGid(const std::string& userName, int& uid, int& gid, std::string& homeDirectory, std::string& shell);

/**
 * @brief SetUserUidGid set the user uid and gid for the current process
 *
 * @param uid user ID
 * @param gid group ID
 * @return std::error_code Success it's success, other value is error
 */
std::error_code SetUserUidGid(int uid, int gid);

} // namespace assist
} // namespace ylg

#endif

