#pragma once

#include <httpex/http_request.h>
#include <httpex/http_manager.h>

#define HTTP_INIT()\
    http::HttpManager::GetInstance()->Start();

#define START_HTTP_REQUEST(request)\
    http::HttpManager::GetInstance()->AddHttpRequest(request);

#define CANCEL_HTTP_REQUEST(request)\
    http::HttpManager::GetInstance()->CancelHttpRequest(request);
