#pragma once

#include <httpex/http_request.h>
#include <httpex/http_manager.h>

#define HTTP_INIT()\
    httpex::HttpManager::GetInstance()->Start();

#define START_HTTP_REQUEST(request)\
    httpex::HttpManager::GetInstance()->AddHttpRequest(request);

#define CANCEL_HTTP_REQUEST(request)\
    httpex::HttpManager::GetInstance()->CancelHttpRequest(request);
