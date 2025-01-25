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

#ifndef _YLG_CORE_ASSIST_EXECUTION_MULTI_QUEUE_H_
#define _YLG_CORE_ASSIST_EXECUTION_MULTI_QUEUE_H_

#include "core/assist/execution_queue.h"

namespace ylg {
namespace assist {

class ExecutionMultiQueue final
{
public:
    ExecutionMultiQueue(const std::string& inName, std::size_t inQueueSize, std::size_t inQueueCount);
    ExecutionMultiQueue(const std::string& inName, std::size_t inQueueSize, std::size_t inQueueCount, std::size_t inConsumerCount);
    ~ExecutionMultiQueue();

public:
    std::error_code Enqueue(const ExecutionQueue::TaskFunctor& task, std::size_t maxRetryTimes = 3);
    std::error_code Enqueue(uint32_t hashCode, const ExecutionQueue::TaskFunctor& task, std::size_t maxRetryTimes = 3);
    void            BlockEnqueue(const ExecutionQueue::TaskFunctor& task);
    void            BlockEnqueue(uint32_t hashCode, const ExecutionQueue::TaskFunctor& task);

private:
    std::string                    _name;
    std::size_t                    _queueSize     = 0;
    std::size_t                    _queueCount    = 0;
    std::size_t                    _consumerCount = 3;
    std::vector<ExecutionQueuePtr> _queues;
};

using ExecutionMultiQueuePtr = std::shared_ptr<ExecutionMultiQueue>;

} // namespace assist
} // namespace ylg

#endif
