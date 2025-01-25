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

#ifndef _YLG_CORE_ASSIST_MACRO_H_
#define _YLG_CORE_ASSIST_MACRO_H_

#define ANONYMOUS_VAR_NAME(t1, t2) t1##t2
#define ANONYMOUS_VAR(t1, t2) ANONYMOUS_VAR_NAME(t1, t2)

#define BEGIN_TRY \
    try           \
    {

#define END_TRY }

#define BEGIN_CATCH(exception, ex) \
    catch (const exception& ex)    \
    {

#define END_CATCH }

#define END_TRY_BEGIN_CATCH(exception, ex) \
    }                                      \
    catch (const exception& ex)            \
    {

#define IGNORE_CATCH_ALL \
    catch (...)          \
    {                    \
    }

#define END_CATCH_AND_BEGIN_CATCH_ALL \
    }                                 \
    catch (...)                       \
    {

#define END_TRY_AND_BEGIN_CATCH_ALL END_CATCH_AND_BEGIN_CATCH_ALL

#define BEGIN_CATCH_ALL \
    catch (...)         \
    {

#define END_CATCH_ALL }

#endif
