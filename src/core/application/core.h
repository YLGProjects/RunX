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

#ifndef _YLG_CORE_APP_CORE_H_
#define _YLG_CORE_APP_CORE_H_

#include "core/application/context.h"
#include "core/application/discovery.h"
#include "core/application/env.h"
#include "third-party/cmdline/cmdline.h"

#include <functional>
#include <memory>
#include <system_error>
#include <vector>

namespace ylg {
namespace app {

using CommandHandler = std::function<std::error_code(ContextPtr ctx)>;

class Core final
{
public:
    Core();
    ~Core();

public:
    /**
     * @brief AddCommand add a flag
     *
     */
    void AddCommand(const FlagInt& flag);
    void AddCommand(const FlagString& flag);
    void AddCommand(const FlagBool& flag);
    void AddCommand(const FlagNoValue& flag);

    /**
     * @brief Run block to run the service
     *
     * @param argc the argv count
     * @param argv the all argv
     * @param executor the executor function, if it exited, the process will be exited
     * @return std::error_code Success for sucess, the others for error
     */
    std::error_code Run(int argc, char* argv[], CommandHandler executor);

    /**
     * @brief Close close the application
     *
     */
    void Close();

private:
    ContextPtr               _ctx;
    EnvPtr                   _env;
    ConfigFilePtr            _file;
    DiscoveryPtr             _discovery;
    cmdline::parser          _parser;
    std::vector<FlagInt>     _iFlags;
    std::vector<FlagString>  _sFlags;
    std::vector<FlagBool>    _bFlags;
    std::vector<FlagNoValue> _nvFlags;
};

using CorePtr = std::shared_ptr<Core>;

} // namespace app
} // namespace ylg

#endif
