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

#ifndef _YLG_CORE_ASSIST_DEFER_H_
#define _YLG_CORE_ASSIST_DEFER_H_

#include "core/assist/macro.h"

#include <functional>

#define DEFER(code) ylg::assist::Defer ANONYMOUS_VAR(L, __LINE__)([&]() { code; });

namespace ylg {
namespace assist {

class Defer final
{
public:
    Defer(std::function<void()> &&func)
        : _functor(std::move(func)){};

    ~Defer()
    {
        if (_functor)
        {
            _functor();
        }
    };

private:
    std::function<void()> _functor;
};

template <typename T>
class DeferAction final
{
public:
    DeferAction(T f)
        : _cleanFunctor(f){};

    ~DeferAction()
    {
        if (_cleanFunctor)
        {
            _cleanFunctor();
        }
    };

private:
    T _cleanFunctor;
};

template <typename T>
DeferAction<T> Finally(T t)
{
    return DeferAction<T>(t);
};

} // namespace assist
} // namespace ylg

#endif
