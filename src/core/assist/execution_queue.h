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

#ifndef _YLG_CORE_ASSIST_EXECUTION_QUEUE_H_
#define _YLG_CORE_ASSIST_EXECUTION_QUEUE_H_

#include <concurrentqueue/moodycamel/blockingconcurrentqueue.h>

#include <atomic>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <string>
#include <vector>

// clang-format off

#define DEQUEUE_BULK_SIZE    4096
#define DEQUEUE_TIMEOUT_USEC 50000

// clang-format on

namespace ylg {
namespace assist {

class ExecutionQueue final
{
public:
    using TaskFunctor = std::function<void()>;

public:
    ExecutionQueue(const std::string& inName, std::size_t inMaxCount);
    ExecutionQueue(const std::string& inName, std::size_t inMaxCount, std::size_t inMaxConsumerCount);
    ~ExecutionQueue();

public:
    std::error_code Enqueue(const TaskFunctor& task, std::size_t maxRetryTimes = 3);
    void            BlockEnqueue(const TaskFunctor& task);

private:
    void Consumer();

private:
    std::atomic_bool                                 _needStop = false;
    std::string                                      _name;
    std::size_t                                      _maxTaskCount = 0;
    moodycamel::BlockingConcurrentQueue<TaskFunctor> _tasks;
    std::size_t                                      _maxConsumerCount = 3;
    std::vector<std::future<void>>                   _consumers;
};

using ExecutionQueuePtr = std::shared_ptr<ExecutionQueue>;

} // namespace assist
} // namespace ylg

#endif
