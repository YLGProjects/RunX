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

#include "server/controller/app.h"
#include "server/controller/api/http/server.h"

#include "internal/controller.h"
#include "internal/error.h"

#include "core/application/service_discovery.h"
#include "core/application/service_registry.h"
#include "core/assist/string.h"
#include "core/assist/time.h"
#include "core/core.h"
#include "core/error/error.h"
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

ylg::internal::ErrorCode App::Run(int argc, char* argv[])
{
    auto ec = ylg::Init();
    if (!ylg::error::IsSuccess(ec))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    _needStop = false;

    ec = InitFlags();

    if (!ylg::error::IsSuccess(ec))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    ec = _core->Run(argc, argv, std::bind(&App::Execute, this, std::placeholders::_1));
    if (!ylg::error::IsSuccess(ec))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    return ylg::internal::ErrorCode::SUCCESS;
}

void App::Close()
{
    _needStop = true;
    _core->Close();
    ylg::Uninit();
}

ylg::internal::ErrorCode App::GuardLoop()
{
    while (!_needStop)
    {
        ylg::assist::MilliSleep(1000);
    }

    LOG_INFO("agent exited");
    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::InitFlags()
{
    ylg::app::FlagString flagConfig;

    flagConfig._fullName    = "config";
    flagConfig._shortName   = 'c';
    flagConfig._description = "the config file";
    flagConfig._value       = "./etc/server.yml";

    _core->AddCommand(flagConfig);

    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::InitLogs()
{
    ylg::log::LogConfig cfg;

    cfg._fileCount  = _localConfig->_maxFileCount;
    cfg._fileSizeMB = _localConfig->_maxFileSizeMB;
    cfg._path       = _localConfig->_logPath;
    cfg._level      = _localConfig->_logLevel;

    auto ec = ylg::log::Logger::Instance().Init(_localConfig->_name, cfg);
    if (!ylg::error::IsSuccess(ec))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::InitDiscovery()
{
    auto                       registry = std::make_shared<ylg::app::ServiceRegistry>(YLG_SERVER_CONTROLLER_APP_SERVICE_REGISTRY,
                                                                                      _localConfig->_discoveryEndpoint,
                                                                                      _localConfig->_discoveryUser,
                                                                                      _localConfig->_discoveryPassword);
    ylg::internal::ServiceInfo service;
    service._serviceID        = registry->GetID();
    service._serviceName      = "controller";
    service._apiAddress       = "";
    service._updatedTimestamp = ylg::assist::TimestampMillisecond();
    service._listeningAddress = ylg::assist::FormatString("%s:%d", _localConfig->_endpointIP.c_str(), _localConfig->_endpointPort);

    auto value = service.ToJSON();
    auto ec    = registry->Run(value);
    if (!ylg::internal::IsSuccess(ec))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    auto discovery = std::make_shared<ylg::app::ServiceDiscovery>(registry->EtcdClient());

    _localConfig->_ctx->SaveRegistry(registry);
    _localConfig->_ctx->SaveDiscovery(discovery);

    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::InitController()
{
    _controller = std::make_shared<Controller>();
    _controller->Run(_localConfig);
    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::InitAPIs()
{
    _httpAPI = std::make_shared<HTTPAPIServer>(_controller);
    _httpAPI->Run("0.0.0.0", 26689);
    return ylg::internal::ErrorCode::SUCCESS;
}

ylg::internal::ErrorCode App::LoadConfig(ylg::app::ContextPtr ctx)
{
    _localConfig->_ctx = ctx;

    if (!ctx->FlagExist("config"))
    {
        return ylg::internal::ErrorCode::ERROR;
    }

    auto cfg = ctx->GetFlagValue<ylg::app::FlagString>("config");
    std::cout << "config:" << cfg._value << std::endl;

    auto ec = ctx->LoadConfig(cfg._value);
    if (!ylg::error::IsSuccess(ec))
    {
        LOG_STD("can not load config file(%s)", cfg._value.c_str());
        return ylg::internal::ErrorCode::ERROR;
    }

    // parse base
    _localConfig->_name    = ctx->GetFileConfig<std::string>("name");
    _localConfig->_version = ctx->GetFileConfig<std::string>("version");

    // parse controller
    _localConfig->_endpointIP   = ctx->GetFileConfig<std::string>("controller.endpoint_ip", "0.0.0.0");
    _localConfig->_endpointPort = ctx->GetFileConfig<uint16_t>("controller.endpoint_port", 26688);

    // parse discovery
    _localConfig->_discoveryEndpoint = ctx->GetFileConfig<std::string>("discovery.endpoints", "");
    _localConfig->_discoveryUser     = ctx->GetFileConfig<std::string>("discovery.user", "");
    _localConfig->_discoveryPassword = ctx->GetFileConfig<std::string>("discovery.password", "");

    // parse log
    _localConfig->_logLevel      = ctx->GetFileConfig<std::string>("log.level", YLG_SERVER_CONTROLLER_LOG_LEVEL_DFT);
    _localConfig->_logPath       = ctx->GetFileConfig<std::string>("log.path", YLG_SERVER_CONTROLLER_LOG_PATH_DFT);
    _localConfig->_maxFileCount  = ctx->GetFileConfig<uint32_t>("log.file_count", YLG_SERVER_CONTROLLER_LOG_FILE_MAX_COUNT_DFT);
    _localConfig->_maxFileSizeMB = ctx->GetFileConfig<uint32_t>("log.file_size", YLG_SERVER_CONTROLLER_LOG_FILE_MAX_FILE_SIZE_MB_DFT);

    return ylg::internal::ErrorCode::SUCCESS;
}

std::error_code App::Execute(ylg::app::ContextPtr ctx)
{
    _localConfig->_ctx = ctx;

    auto ec = LoadConfig(ctx);
    if (!ylg::internal::IsSuccess(ec))
    {
        return ec;
    }

    ec = InitLogs();
    if (!ylg::internal::IsSuccess(ec))
    {
        return ec;
    }

    ec = InitDiscovery();
    if (!ylg::internal::IsSuccess(ec))
    {
        return ec;
    }

    ec = InitController();
    if (!ylg::internal::IsSuccess(ec))
    {
        return ec;
    }

    ec = InitAPIs();
    if (!ylg::internal::IsSuccess(ec))
    {
        return ec;
    }

    LOG_INFO("RunX Controller Server Started");
    return GuardLoop();
}
