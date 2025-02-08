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

#ifndef _YLG_SERVER_TRANSFER_APP_H_
#define _YLG_SERVER_TRANSFER_APP_H_

#include "server/transfer/api/http/server.h"
#include "server/transfer/configuration.h"
#include "server/transfer/transfer.h"

#include "core/application/core.h"

#include <future>

class App final
{
public:
    App();
    ~App();

public:
    std::error_code Run(int argc, char *argv[]);
    void            Close();

private:
    std::error_code GuardLoop();
    void            DumpConfiguration();
    std::error_code InitFlags();
    std::error_code InitLogs();
    std::error_code InitTransfer();
    std::error_code InitAPIs();
    std::error_code LoadConfig(ylg::app::ContextPtr ctx);
    std::error_code Execute(ylg::app::ContextPtr ctx);

private:
    std::future<void>         _controllerRun;
    ConfigurationPtr          _localConfig;
    HTTPAPIServerPtr          _httpAPI  = nullptr;
    std::shared_ptr<Transfer> _transfer = nullptr;
    ylg::app::CorePtr         _core     = nullptr;
    std::atomic_bool          _needStop = false;
};

#endif

