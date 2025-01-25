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

#ifndef _YLG_CORE_ASSIST_TIME_H_
#define _YLG_CORE_ASSIST_TIME_H_

#include <cstdint>
#include <ctime>
#include <string>

namespace ylg {
namespace assist {

/**
 * @brief Sleep sleep some seconds
 *
 * @param secs second value
 */
void Sleep(uint32_t secs);

/**
 * @brief MilliSleep sleep some milliseconds
 *
 * @param milliSecs millisecond value
 */
void MilliSleep(uint32_t milliSecs);

/**
 * @brief Timezone return the current timezone value
 *
 * @return int timezone value
 */
int Timezone();

/**
 * @brief TimestampSecond return the second timestamp
 *
 * @return uint32_t second timestamp
 */
uint32_t TimestampSecond();

/**
 * @brief TimestampMillisecond return the millisecond timestamp
 *
 * @return uint64_t millisecond timestamp
 */
uint64_t TimestampMillisecond();

/**
 * @brief uint64_t TimestampMicrosecond return the microsecond timestamp
 *
 * @return uint64_t microsecond timestamp
 */
uint64_t TimestampMicrosecond();

/**
 * @brief uint64_t TimestampTickCountSecond return the tick count second timestamp
 *
 * @return uint64_t tick count second
 */
uint64_t TimestampTickCountSecond();

/**
 * @brief TimestampTickCountMillisecond return the tick count millisecond timestamp
 *
 * @return uint64_t tick count millisecond
 */
uint64_t TimestampTickCountMillisecond();

/**
 * @brief TimestampTickCountMicrosecond return the tick count microsecond timestamp
 *
 * @return uint64_t tick count microsecond
 */
uint64_t TimestampTickCountMicrosecond();

/**
 * @brief TimeToString format time to string
 *
 * @param time the target time
 * @return std::string string time value
 */
std::string TimeToString(std::time_t time);
std::string TimeToString(std::time_t time, const std::string& formatter);

} // namespace assist
} // namespace ylg

#endif
