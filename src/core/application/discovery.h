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

#ifndef _YLG_CORE_APP_DISCOVERY_H_
#define _YLG_CORE_APP_DISCOVERY_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ylg {
namespace app {

class Discovery final
{
public:
    enum Event
    {
        Updated = 0,
        Deleted = 1,
        Created = 2
    };

    using CallbackFunctor = std::function<void(Event event, const std::string& key, const std::vector<std::string>& values)>;

public:
    /**
     * @brief Watch watch the key‘s event
     *       if the value of the key has changed, the callback will be callbacked
     *
     * @param key the key that is monitored
     * @param callback the event callback function
     * @return std::error_code if success return std::error_code::Success, other value is error.
     */
    std::error_code Watch(const std::string& key, CallbackFunctor callback);

    /**
     * @brief GetList get the values by the key
     *
     * @param key the key
     * @param elements the returned values
     * @return std::error_code if success return std::error_code::Success, other value is error.
     */
    std::error_code GetList(const std::string& key, std::vector<std::string>& elements);

    /**
     * @brief GetValue get the value by the key
     *
     * @param key the key
     * @param value the returned value
     * @return std::error_code if success return std::error_code::Success, other value is error.
     */
    std::error_code GetValue(const std::string& key, std::string& value);

    /**
     * @brief Start start the discovery
     *
     * @param endpoints the configuration center address
     * @param errMsg if the errMsg is not nullptr, it will be seted when make some exceptions.
     * @return std::error_code if success return std::error_code::Success, other value is error.
     */
    std::error_code Start(const std::string& endpoints, std::string* errMsg);

    /**
     * @brief Stop stop the discovery
     *
     */
    void Stop();

private:
    std::string _endpoints;
};

using DiscoveryPtr = std::shared_ptr<Discovery>;

} // namespace app
} // namespace ylg

#endif
