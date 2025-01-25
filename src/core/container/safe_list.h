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

#ifndef _YLG_CORE_CONTAINER_SAFE_LIST_H_
#define _YLG_CORE_CONTAINER_SAFE_LIST_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <list>
#include <mutex>
#include <shared_mutex>

namespace ylg {
namespace container {

template <typename T>
class SafeList final
{
public:
    /**
     * @brief PushBack push the element at the list end
     *
     * @param ele the element will be pushed into the list
     */
    void PushBack(T ele)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.push_back(ele);
    }

    /**
     * @brief Front get the element at the list front
     *
     * @param front the element was returned
     */
    void Front(T& front)
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        front = _elements.front();
    }

    /**
     * @brief Back returns the data at the last element of the list.
     *
     * @param back the element was returned
     */
    void Back(T& back)
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        back = _elements.back();
    }

    /**
     * @brief PopBack delete the element at the last of the list
     *
     */
    void PopBack()
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.pop_back();
    }

    /**
     * @brief PopFront delete the element at the front of the list
     *
     */
    void PopFront()
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
       _elements.pop_front();
    }

    /**
     * @brief Foreach foreach all the elements and call the callback for each element
     *
     * @param callback the callback function
     */
    void Foreach(std::function<void(T)> callback)
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);

        for (auto ele : _elements)
        {
            callback(ele);
        }
    }

    /**
     * @brief Delete delete the element from the list when the needDelete function return true
     *
     * @param needDelete the function used to check if the element need to be deleted
     */
    void Delete(std::function<bool(T)> needDelete)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);

        for (auto eleIter = _elements.begin(); eleIter != _elements.end();)
        {

            if (needDelete(*eleIter))
            {
                eleIter = _elements.erase(eleIter);
            }
            else
            {
                ++eleIter;
            }
        }
    }

    /**
     * @brief Swap exchanges the elements between two lists
     *
     * @param swappedElements the elements will be exchanged
     */
    void Swap(std::list<T>& swappedElements)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.swap(swappedElements);
    }

    /**
     * @brief CopyTo copy this list values to copiedElements
     *
     * @param copiedElements used to received all the values
     */
    void CopyTo(std::list<T>& copiedElements)
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        std::copy(_elements.begin(), _elements.end(), std::back_inserter(copiedElements));
    }

    /**
     * @brief Count return the elements count of this list
     *
     * @return std::size_t
     */
    std::size_t Count()
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _elements.size();
    }

    /**
     * @brief Empty check the list if it's empty
     *
     * @return true this list is empty
     * @return false this list is not empty
     */
    bool Empty()
    {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _elements.empty();
    }

    /**
     * @brief Clean clean all elements from this list
     *
     */
    void Clean()
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _elements.clear();
    }

private:
    std::shared_mutex _mutex;
    std::list<T>      _elements;
};

} // namespace container
} // namespace ylg

#endif
