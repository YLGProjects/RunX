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

#include "core/assist/string.h"
#include "core/assist/math.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

namespace ylg {
namespace assist {

bool IsNumber(const std::string& val)
{
    std::istringstream iss(val);
    double             number;
    return iss >> number && iss.eof();
}

int Comapre(const std::string& val1, const std::string& val2, bool ignoreCase)
{
    std::string lower1(val1);
    std::string lower2(val2);

    std::transform(val1.begin(), val1.end(), lower1.begin(), tolower);
    std::transform(val2.begin(), val2.end(), lower2.begin(), tolower);

    return lower1.compare(lower2);
}

void Replace(std::string& value, const std::string& oldstr, const std::string& newstr)
{
    if (oldstr.empty())
    {
        return;
    }

    std::size_t newSize = newstr.size();
    std::size_t oldSize = oldstr.size();

    for (auto pos = value.find(oldstr, 0); pos != std::string::npos; pos = value.find(oldstr, pos + newSize))
    {
        value.replace(pos, oldSize, newstr);
    }
}

void Split(const std::string& value, const std::string& delimiter, std::vector<std::string>& elements)
{
    std::string::size_type pos1 = 0;
    std::string::size_type pos2 = value.find(delimiter);

    while (std::string::npos != pos2)
    {
        elements.push_back(value.substr(pos1, pos2 - pos1));

        pos1 = pos2 + delimiter.size();
        pos2 = value.find(delimiter, pos1);
    }

    if (pos1 != value.length())
    {
        elements.push_back(value.substr(pos1));
    }
}

void TrimRight(std::string& value, const std::string& sequence)
{
    std::size_t pos = value.find_last_not_of(sequence);
    if (pos != std::string::npos)
    {
        value = value.substr(0, pos + 1);
    }
}

void TrimLeft(std::string& value, const std::string& sequence)
{
    std::size_t pos = value.find_first_not_of(sequence);

    if (pos != std::string::npos)
    {
        value = value.substr(pos);
    }
}

void Trim(std::string& value, const std::string& sequence)
{
    for (auto iter = value.begin(); iter != value.end();)
    {
        if (sequence.find(*iter) != std::string::npos)
        {
            iter = value.erase(iter);
            continue;
        }

        ++iter;
    }
}

std::string ToString(const std::vector<std::string>& elements, const std::string& delimiter)
{
    std::string result;

    for (int i = 0; i < elements.size(); ++i)
    {
        if (!result.empty())
        {
            result.append(delimiter);
        }

        result.append(elements.at(i));
    }

    return result;
}

bool ToBool(const std::string& value, bool defaultValue)
{
    bool result = false;

    std::istringstream iss(value);
    iss >> std::boolalpha >> result;

    if (iss.fail())
    {
        return defaultValue;
    }

    return result;
}

uint16_t Hash(const std::string& data)
{
    return CRC16(data.data(), data.length());
}

} // namespace assist
} // namespace ylg
