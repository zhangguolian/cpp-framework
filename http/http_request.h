/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>

namespace http {

class HttpRequest {
public:
    class Delegate {
    public:
        virtual void OnHttpRequestComplete(std::shared_ptr<HttpRequest> request) = 0;
    };

    enum HttpMode {
        GET = 0,
        POST,
    };

    enum Status {
        INIT = 0,
        IO_PENDING,
        SUCCESS,
        CANCELED,
        FAILED,
    };

    HttpRequest(HttpMode http_mode,
                const std::string& url,
                Delegate* delegate);
    ~HttpRequest();

    int http_code();
    void set_http_code(int http_code);

    HttpMode http_mode();
    void set_http_mode(HttpMode http_mode);
    
    const std::string& url();
    void set_url(const std::string& url);

    const std::map<std::string, std::string>& params();
    void add_params(const std::string& key,
                    const std::string& value);

    Delegate* delegate();
    void set_delegate(Delegate* delegate);

    const std::string& cookie();
    void set_cookie(const std::string& cookie);

    Status status();
    void set_status(Status status);

    const std::string& response();
    void set_response(const std::string& response);

private:
    int http_code_;
    Status status_;
    HttpMode http_mode_;
    std::string url_;
    std::string cookie_;
    std::string response_;
    Delegate* delegate_;
    std::map<std::string, std::string> params_;
};

};