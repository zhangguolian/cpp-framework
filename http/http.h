#pragma once

#include <http/http_buffer.h>
#include <http/http_request.h>
#include <http/http_manager.h>

#define HTTP_INIT()\
    http::HttpManager::GetInstance()->Start();

#define START_HTTP_REQUEST(request)\
    http::HttpManager::GetInstance()->AddHttpRequest(request);

#define CANCEL_HTTP_REQUEST(request)\
    http::HttpManager::GetInstance()->CancelHttpRequest(request);
