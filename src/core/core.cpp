#include "core/core.h"
#include "agent/error.h"

#include <curl/curl.h>

namespace ylg {

std::error_code Init()
{
    curl_global_init(CURL_GLOBAL_ALL);
    return MakeSuccess();
}

void Uninit()
{
    curl_global_cleanup();
}

} // namespace ylg

