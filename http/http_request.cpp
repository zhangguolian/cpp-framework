#include <http/http_request.h>

#include <http/http_manager.h>

namespace http {

HttpRequest::HttpRequest(HttpMode http_mode,
                         const std::string& url,
                         Delegate* delegate)
            : status_(INIT)
            , http_mode_(http_mode)
            , url_(url)
            , delegate_(delegate) {

}
HttpRequest::~HttpRequest() {
    delegate_ = NULL;
}

void HttpRequest::Start() {
    HttpManager::GetInstance()->AddHttpRequest(this);
}
void HttpRequest::Cancel() {
    HttpManager::GetInstance()->CancelHttpRequest(this);
}

int HttpRequest::http_code() {
    return http_code_;
}
void HttpRequest::set_http_code(int http_code) {
    http_code_ = http_code;
}

HttpRequest::HttpMode HttpRequest::http_mode() {
    return http_mode_;
}
void HttpRequest::set_http_mode(HttpMode http_mode) {
    http_mode_ = http_mode;
}

const std::string& HttpRequest::url() {
    return url_;
}
void HttpRequest::set_url(const std::string& url) {
    url_ = url;
}

const std::map<std::string, std::string>& HttpRequest::params() {
    return params_;
}
void HttpRequest::add_params(const std::string& key,
                             const std::string& value) {
    params_[key] = value;
}

HttpRequest::Delegate* HttpRequest::delegate() {
    return delegate_;
}
void HttpRequest::set_delegate(Delegate* delegate) {
    delegate_ = delegate; 
}

const std::string& HttpRequest::cookie() {
    return cookie_;
}
void HttpRequest::set_cookie(const std::string& cookie) {
    cookie_ = cookie;
}

HttpRequest::Status HttpRequest::status() {
    return status_;
}
void HttpRequest::set_status(Status status) {
    status_ = status;
}

const std::string& HttpRequest::response() {
    return response_;
}
void HttpRequest::set_response(const std::string& response) {
    response_ = response;
}

}