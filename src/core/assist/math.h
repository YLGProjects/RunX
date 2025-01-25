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

#ifndef _YLG_CORE_ASSIST_MATH_H_
#define _YLG_CORE_ASSIST_MATH_H_

#include <cstdint>
#include <string>

namespace ylg {
namespace assist {

/**
 * @brief CRC16 imp according to CCITT standards
 *
 * @param buf the inputed buffer
 * @param len the inputed buffer size
 *
 * @return uint16_t 16 bits hash integer value
 */
uint16_t CRC16(const char* buf, int len);

/**
 * @brief UUID generate a new UUID string
 *
 * @return std::string UUID
 */
std::string UUID();

/**
 * @brief RandomNumber generate random number
 *
 * @param max the max random value
 * @return uint32_t
 */
uint32_t RandomNumber(uint32_t max);

/**
 * @brief RandomString generate random string
 *
 * @param length the random string length
 *
 * @return std::string random string
 */
std::string RandomString(uint32_t length);

} // namespace assist
} // namespace ylg

#endif
