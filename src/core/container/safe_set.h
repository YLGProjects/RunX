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

#ifndef _YLG_CORE_CONTAINER_SAFE_SET_H_
#define _YLG_CORE_CONTAINER_SAFE_SET_H_

#include <cstddef>
#include <mutex>
#include <set>
#include <shared_mutex>

namespace ylg {
namespace container {

template <typename T>
class SafeSet final
{
public:
    /**
     * @brief Count return the element count of this set
     *
     * @return std::size_t
     */
    std::size_t Count()
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _elements.size();
    }

    /**
     * @brief Insert insert the value into this set
     *
     * @param value the inserted value
     * @return true success
     * @return false failure
     */
    bool Insert(const T& value)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);

        auto result = _elements.insert(value);
        return result.first != _elements.end();
    }

    /**
     * @brief Empty checks whether this set is empty
     *
     * @return true this set is empty
     * @return false this set is not empty
     */
    bool Empty()
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _elements.empty();
    }

    /**
     * @brief Clean clears this set
     *
     */
    void Clean()
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.clear();
    }

    /**
     * @brief Swap swaps the contents
     *
     * @param swappedElements the new contents
     */
    void Swap(T& swappedElements)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.swap(swappedElements);
    }

    /**
     * @brief Exists check whether the value exists in this set
     *
     * @param value the element found in this set
     * @return true found this element in this set
     * @return false do not find this element in this set
     */
    bool Exists(const T& value)
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _elements.count(value) > 0;
    }

private:
    std::shared_mutex _mutex;
    std::set<T>       _elements;
};

} // namespace container
} // namespace ylg

#endif
