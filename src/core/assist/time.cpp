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

#include "core/assist/time.h"
#include "core/assist/memory.h"

#include <chrono>
#include <cstdlib>

#include <unistd.h>

namespace ylg {
namespace assist {

void Sleep(uint32_t secs)
{
    sleep(secs);
}

void MilliSleep(uint32_t milliSecs)
{
    usleep(milliSecs * 1000);
}

int Timezone()
{
    std::time_t now     = std::time(nullptr);
    std::tm     localTM = {0};

    char timezone[10];
    ZeroMemory(timezone, sizeof(timezone));

    localtime_r(&now, &localTM);
    std::strftime(timezone, sizeof(timezone), "%z", &localTM);

    return std::atoi(timezone) / 100;
}

uint32_t TimestampSecond()
{
    std::chrono::system_clock::time_point now     = std::chrono::system_clock::now();
    std::chrono::seconds                  seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    return seconds.count();
}

uint64_t TimestampMillisecond()
{
    std::chrono::system_clock::time_point now          = std::chrono::system_clock::now();
    std::chrono::milliseconds             milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return milliseconds.count();
}

uint64_t TimestampMicrosecond()
{
    std::chrono::system_clock::time_point now          = std::chrono::system_clock::now();
    std::chrono::microseconds             microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return microseconds.count();
}

uint64_t TimestampTickCountSecond()
{
    std::chrono::steady_clock::time_point now     = std::chrono::steady_clock::now();
    std::chrono::seconds                  seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    return seconds.count();
}

uint64_t TimestampTickCountMillisecond()
{
    std::chrono::steady_clock::time_point now          = std::chrono::steady_clock::now();
    std::chrono::milliseconds             milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return milliseconds.count();
}

uint64_t TimestampTickCountMicrosecond()
{
    std::chrono::steady_clock::time_point now          = std::chrono::steady_clock::now();
    std::chrono::microseconds             microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    return microseconds.count();
}

std::string TimeToString(std::time_t time)
{
    return TimeToString(time, "%Y-%m-%d %H:%M:%S");
}

std::string TimeToString(std::time_t time, const std::string& formatter)
{
    std::tm localTM = {0};

    localtime_r(&time, &localTM);

    char formatedTime[24];
    ZeroMemory(formatedTime, sizeof(formatedTime));

    std::strftime(formatedTime, sizeof(formatedTime), formatter.c_str(), &localTM);
    return std::string(formatedTime);
}

} // namespace assist
} // namespace ylg
