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

#include "server/app.h"
#include "server/error.h"

#include "core/assist/time.h"
#include "core/log/log.h"

App::App()
{
    _core        = std::make_shared<ylg::app::Core>();
    _localConfig = std::make_shared<Configuration>();
}

App::~App()
{
    Close();
}

std::error_code App::Run(int argc, char *argv[])
{
    _needStop = false;

    auto ec = InitFlags();

    if (!IsSuccess(ec))
    {
        return ec;
    }

    return _core->Run(argc, argv, std::bind(&App::Execute, this, std::placeholders::_1));
}

void App::Close()
{
    _needStop = true;
}

std::error_code App::GuardLoop()
{
    while (!_needStop)
    {
        ylg::assist::MilliSleep(1000);
    }

    LOG_INFO("agent exited");
    return MakeSuccess();
}

void App::DumpConfiguration()
{
    LOG_INFO("{}", DumpConfig(*_localConfig));
}

std::error_code App::InitFlags()
{
    ylg::app::FlagString flagConfig;

    flagConfig._fullName    = "config";
    flagConfig._shortName   = 'c';
    flagConfig._description = "the config file";
    flagConfig._value       = "./etc/server.yml";

    _core->AddCommand(flagConfig);

    return MakeSuccess();
}

std::error_code App::InitLogs()
{
    ylg::log::LogConfig cfg;

    cfg._fileCount  = _localConfig->_maxFileCount;
    cfg._fileSizeMB = _localConfig->_maxFileSizeMB;
    cfg._path       = _localConfig->_logPath;
    cfg._level      = _localConfig->_logLevel;

    return ylg::log::Logger::Instance().Init(_localConfig->_name, cfg);
}

std::error_code App::InitController()
{
    _controller = std::make_shared<Controller>();
    _controller->Run(_localConfig->_endpointIP, _localConfig->_endpointPort);
    return MakeSuccess();
}

std::error_code App::LoadConfig(ylg::app::ContextPtr ctx)
{
    _localConfig->_ctx = ctx;

    if (!ctx->FlagExist("config"))
    {
        return MakeError(ErrorCode::Error);
    }

    auto cfg = ctx->GetFlagValue<ylg::app::FlagString>("config");
    std::cout << "config:" << cfg._value << std::endl;

    auto ec = ctx->LoadConfig(cfg._value);
    if (!IsSuccess(ec))
    {
        LOG_STD("can not load config file(%s)", cfg._value.c_str());
        return ec;
    }

    // parse base
    _localConfig->_name    = ctx->GetFileConfig<std::string>("name");
    _localConfig->_version = ctx->GetFileConfig<std::string>("version");

    // parse controller
    _localConfig->_endpointIP   = ctx->GetFileConfig<std::string>("controller.endpoint.ip", "0.0.0.0");
    _localConfig->_endpointPort = ctx->GetFileConfig<uint16_t>("controller.endpoint.port", 26688);

    // parse log
    _localConfig->_logLevel      = ctx->GetFileConfig<std::string>("log.level", YLG_SERVER_LOG_LEVEL_DFT);
    _localConfig->_logPath       = ctx->GetFileConfig<std::string>("log.path", YLG_SERVER_LOG_PATH_DFT);
    _localConfig->_maxFileCount  = ctx->GetFileConfig<uint32_t>("log.file-count", YLG_SERVER_LOG_FILE_MAX_COUNT_DFT);
    _localConfig->_maxFileSizeMB = ctx->GetFileConfig<uint32_t>("log.file-sizeMB", YLG_SERVER_LOG_FILE_MAX_FILE_SIZE_MB_DFT);

    return ec;
}

std::error_code App::Execute(ylg::app::ContextPtr ctx)
{
    _localConfig->_ctx = ctx;

    auto ec = LoadConfig(ctx);
    if (!IsSuccess(ec))
    {
        LOG_ERROR("failed to load config. errmsg({}:{})", ec.value(), ec.message());
        return ec;
    }

    ec = InitLogs();
    if (!IsSuccess(ec))
    {
        LOG_ERROR("failed to init log. err-msg({}:{})", ec.value(), ec.message());
        return ec;
    }

    DumpConfiguration();

    ec = InitController();
    if (!IsSuccess(ec))
    {
        LOG_ERROR("failed to init controller. err-msg({}:{})", ec.value(), ec.message());
        return ec;
    }

    return GuardLoop();
}
