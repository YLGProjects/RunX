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

#include "core/assist/execution_multi_queue.h"
#include "core/assist/execution_queue.h"
#include "core/assist/string.h"

#include <atomic>
#include <memory>

namespace ylg {
namespace assist {

ExecutionMultiQueue::ExecutionMultiQueue(const std::string& inName, std::size_t inQueueSize, std::size_t inQueueCount)
{
    _name       = inName;
    _queueSize  = inQueueSize;
    _queueCount = inQueueCount;

    for (auto idx = 0; idx < inQueueCount; ++idx)
    {
        auto qname = FormatString("%s-%d", _name.c_str(), idx);
        _queues.push_back(std::make_shared<ExecutionQueue>(qname, _queueSize));
    }
}

ExecutionMultiQueue::ExecutionMultiQueue(const std::string& inName, std::size_t inQueueSize, std::size_t inQueueCount, std::size_t inConsumerCount)
{
    _name          = inName;
    _queueSize     = inQueueSize;
    _queueCount    = inQueueCount;
    _consumerCount = inConsumerCount;

    for (auto idx = 0; idx < _queueCount; ++idx)
    {
        auto qname = FormatString("%s-%d", _name.c_str(), idx);
        _queues.push_back(std::make_shared<ExecutionQueue>(qname, _queueSize));
    }
}

ExecutionMultiQueue::~ExecutionMultiQueue()
{
    _queues.clear();
}

std::error_code ExecutionMultiQueue::Enqueue(const ExecutionQueue::TaskFunctor& task, std::size_t maxRetryTimes)
{

    static std::atomic_uint64_t idx = 0;

    auto pos = ++idx % _queueCount;
    return _queues[pos]->Enqueue(task, maxRetryTimes);
}

std::error_code ExecutionMultiQueue::Enqueue(uint32_t hashCode, const ExecutionQueue::TaskFunctor& task, std::size_t maxRetryTimes)
{
    auto pos = hashCode % _queueCount;
    return _queues[pos]->Enqueue(task, maxRetryTimes);
}

void ExecutionMultiQueue::BlockEnqueue(const ExecutionQueue::TaskFunctor& task)
{
    static std::atomic_uint64_t idx = 0;

    auto pos = ++idx % _queueCount;
    _queues[pos]->BlockEnqueue(task);
}

void ExecutionMultiQueue::BlockEnqueue(uint32_t hashCode, const ExecutionQueue::TaskFunctor& task)
{
    auto pos = hashCode % _queueCount;
    _queues[pos]->BlockEnqueue(task);
}

} // namespace assist
} // namespace ylg
