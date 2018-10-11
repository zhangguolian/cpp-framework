#include <http/http_manager.h>

#include <curl/easy.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <http/http_request.h>
#include <base/base.h>

namespace http {

HttpManager* HttpManager::http_manager_ = NULL;

std::string MapToUrlQuery(const std::map<std::string, std::string>& params) {
    std::string result = "";
    for (auto iter = params.begin(); iter != params.end(); iter++) {
        if (result == "") {
            result += iter->first + "=" + iter->second;
        } else {
            result += "&" + iter->first + "=" + iter->second;
        }
    }

    return result;
}

HttpManager::HttpManager()
            : is_running_(false)
            , still_running_(0)
            , curl_m_(NULL) {

}
HttpManager::~HttpManager() {
    Cancel();
}

HttpManager* HttpManager::GetInstance() {
    if (http_manager_ == NULL) {
        http_manager_ = new HttpManager();
    }

    return http_manager_;
}

void HttpManager::Start() {
    if (is_running_) {
        return;
    }

    if (thread_.get() == NULL) {
        thread_.reset(new async::Thread());
        thread_->PostTask(boost::bind(&HttpManager::Start, this));
        return;
    }

    is_running_ = true;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_m_ = curl_multi_init();
    curl_multi_setopt(curl_m_, CURLMOPT_SOCKETFUNCTION, sock_cb);
    curl_multi_setopt(curl_m_, CURLMOPT_SOCKETDATA, curl_m_);
    curl_multi_setopt(curl_m_, CURLMOPT_TIMERFUNCTION, multi_timer_cb);
    curl_multi_setopt(curl_m_, CURLMOPT_TIMERDATA, curl_m_);
}
void HttpManager::Cancel() {
    if (!is_running_) {
        return;  
    }

    for (auto iter = callback_data_list_.begin(); iter != callback_data_list_.end(); iter++) {
        curl_multi_remove_handle(curl_m_, iter->first);
        curl_easy_cleanup(iter->first);
    }
    curl_multi_cleanup(curl_m_);
    curl_m_ = NULL;
    request_list_.clear();
    callback_data_list_.clear();
}

void HttpManager::AddHttpRequest(std::shared_ptr<HttpRequest> request) {
    if (*thread_ != CURRENT_THREAD) {
        thread_->PostTask(boost::bind(&HttpManager::AddHttpRequest, this, request));
        return;
    }

    if (request == NULL || request_list_.find(request) != request_list_.end()) {
        return;
    }

    CURLData* curl_data = CreateCURLData(request);

    request_list_[request].reset(curl_data);
    callback_data_list_[curl_data->curl_].request = request;
    curl_multi_add_handle(curl_m_, curl_data->curl_);
}
void HttpManager::CancelHttpRequest(std::shared_ptr<HttpRequest> request) {
    if (*thread_ != CURRENT_THREAD) {
        thread_->PostTask(boost::bind(&HttpManager::CancelHttpRequest, this, request));
        return;
    }

    auto iter = request_list_.find(request);
    if (iter == request_list_.end()) {
        return;
    }

    curl_multi_remove_handle(curl_m_, iter->second->curl_);
    curl_easy_cleanup(iter->second->curl_);
    callback_data_list_.erase(iter->second->curl_);
    request_list_.erase(request);

    return;
}

HttpManager::CURLData* HttpManager::CreateCURLData(std::shared_ptr<HttpRequest> request) {
    CURLData* curl_data = new CURLData();
    curl_data->curl_ = curl_easy_init();

    std::string url = request->url();
    if (!request->params().empty()) {
        if (request->http_mode() == HttpRequest::HttpMode::GET) {
            url += "?" + MapToUrlQuery(request->params());
        } else {
            curl_data->headers_ = curl_slist_append(curl_data->headers_, "Content-Type: application/x-www-form-urlencoded");
            curl_data->headers_ = curl_slist_append(curl_data->headers_, "Accept-Language: zh-cn");
            curl_data->post_data_ = MapToUrlQuery(request->params());
            curl_easy_setopt(curl_data->curl_, CURLOPT_HTTPHEADER, curl_data->headers_);
            curl_easy_setopt(curl_data->curl_, CURLOPT_POSTFIELDSIZE, curl_data->post_data_.size());
            curl_easy_setopt(curl_data->curl_, CURLOPT_POSTFIELDS, curl_data->post_data_.c_str());
            curl_easy_setopt(curl_data->curl_, CURLOPT_POST, 1);
        }
    }

    if (request->url().find("https://") != std::string::npos) {
        curl_easy_setopt(curl_data->curl_, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl_data->curl_, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    if (!request->cookie().empty()) {
        curl_easy_setopt(curl_data->curl_, CURLOPT_COOKIE, request->cookie().c_str());
    }  

    curl_easy_setopt(curl_data->curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_data->curl_, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl_data->curl_, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl_data->curl_, CURLOPT_MAXREDIRS, 5L);
    curl_easy_setopt(curl_data->curl_, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_data->curl_, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl_data->curl_, CURLOPT_WRITEDATA, curl_data->curl_);
    /* call this function to get a socket */
    curl_easy_setopt(curl_data->curl_, CURLOPT_OPENSOCKETFUNCTION, opensocket);
    /* call this function to close a socket */
    curl_easy_setopt(curl_data->curl_, CURLOPT_CLOSESOCKETFUNCTION, close_socket);

    return curl_data;
}

void HttpManager::HttpRequestComplete(CURLMsg* msg) {
    if (!msg || !msg->easy_handle) {
        return;
    }

    auto iter = callback_data_list_.find(msg->easy_handle);
    if (iter == callback_data_list_.end()) {
        return;
    }

    // test {
    // int http_code = -1;
    // if (msg->data.result == CURLE_OK) {
    //     curl_easy_getinfo(msg->easy_handle, CURLINFO_RESPONSE_CODE, &http_code);
    // }

    int http_code = 200;
    // }

    if (http_code == 200 || http_code == 206) {
        iter->second.request->set_status(HttpRequest::Status::SUCCESS);
        iter->second.request->set_response(iter->second.buffer);
    } else {
        iter->second.request->set_status(HttpRequest::Status::FAILED);
        iter->second.request->set_http_code(http_code);
    }

    iter->second.request->delegate()->OnHttpRequestComplete(iter->second.request);

    curl_multi_remove_handle(curl_m_, msg->easy_handle);
    request_list_.erase(iter->second.request);
    callback_data_list_.erase(msg->easy_handle);

    return;
}

int HttpManager::multi_timer_cb(CURLM *multi, long timeout_ms) {
    if(timeout_ms > 0) {
        /* update timer */
        http_manager_->timer_.CreateOnceTimerTask(boost::bind(&timer_cb), 
            boost::posix_time::millisec(timeout_ms), 
            http_manager_->thread_);
    } else if(timeout_ms == 0) {
        /* call timeout function immediately */
        timer_cb();
    }

    return 0;
}
void HttpManager::timer_cb() {
    curl_multi_socket_action(http_manager_->curl_m_, CURL_SOCKET_TIMEOUT, 0,
                             &http_manager_->still_running_);

    check_multi_info();
}
int HttpManager::sock_cb(CURL* curl, curl_socket_t sock, int what, void* cbp, void* sockp) {
    int* actionp = (int*)sockp;

    if(what == CURL_POLL_REMOVE) {
        remsock(actionp);
    } else {
        if(!actionp) {
            addsock(sock, curl, what);
        } else {;
            setsock(actionp, sock, curl, what, *actionp);
        }
    }

    return 0;
}

void HttpManager::addsock(curl_socket_t sock, CURL* easy, int action) {
    /* fdp is used to store current action */
    int* fdp = (int *)calloc(sizeof(int), 1);

    setsock(fdp, sock, easy, action, 0);
    curl_multi_assign(http_manager_->curl_m_, sock, fdp);
}
void HttpManager::setsock(int *fdp, curl_socket_t sock, CURL* easy, int act, int oldact) {
    auto iter = http_manager_->socket_list_.find(sock);
    if(iter == http_manager_->socket_list_.end()) {
        return;
    }

    boost::asio::ip::tcp::socket* tcp_socket = iter->second;
    *fdp = act;

    if(act == CURL_POLL_IN) {
        if(oldact != CURL_POLL_IN && oldact != CURL_POLL_INOUT) {
            tcp_socket->async_read_some(boost::asio::null_buffers(),
                                        boost::bind(&event_cb, sock,
                                                    CURL_POLL_IN, _1, fdp));
        }
    } else if(act == CURL_POLL_OUT) {
        if(oldact != CURL_POLL_OUT && oldact != CURL_POLL_INOUT) {
            tcp_socket->async_write_some(boost::asio::null_buffers(),
                                         boost::bind(&event_cb, sock,
                                                     CURL_POLL_OUT, _1, fdp));
        }
    } else if(act == CURL_POLL_INOUT) {
        if(oldact != CURL_POLL_IN && oldact != CURL_POLL_INOUT) {
            tcp_socket->async_read_some(boost::asio::null_buffers(),
                                        boost::bind(&event_cb, sock,
                                                    CURL_POLL_IN, _1, fdp));
        }
        if(oldact != CURL_POLL_OUT && oldact != CURL_POLL_INOUT) {
            tcp_socket->async_write_some(boost::asio::null_buffers(),
                                         boost::bind(&event_cb, sock,
                                                    CURL_POLL_OUT, _1, fdp));
        }
    }
}
void HttpManager::remsock(int* fd) {
    if(fd) {
        free(fd);
    }
}
void HttpManager::event_cb(curl_socket_t sock, int action, const boost::system::error_code& error, int *fdp) {
    auto iter = http_manager_->socket_list_.find(sock);
    if(iter == http_manager_->socket_list_.end()) {
        return;
    }

    /* make sure the event matches what are wanted */
    if(*fdp == action || *fdp == CURL_POLL_INOUT) {
        if(error) {
            action = CURL_CSELECT_ERR;
        }
        curl_multi_socket_action(http_manager_->curl_m_, sock, 
                                 action, &http_manager_->still_running_);

        check_multi_info();

        /* keep on watching.
            * the socket may have been closed and/or fdp may have been changed
            * in curl_multi_socket_action(), so check them both */
        if(!error && (*fdp == action || *fdp == CURL_POLL_INOUT)) {
            boost::asio::ip::tcp::socket* tcp_socket = iter->second;
            if(action == CURL_POLL_IN) {
                tcp_socket->async_read_some(boost::asio::null_buffers(),
                                            boost::bind(&event_cb, sock,
                                                        action, _1, fdp));
            }
            if(action == CURL_POLL_OUT) {
                tcp_socket->async_write_some(boost::asio::null_buffers(),
                                             boost::bind(&event_cb, sock,
                                                         action, _1, fdp));
            }
        }
    } 
}

curl_socket_t HttpManager::opensocket(void* clientp, curlsocktype purpose, struct curl_sockaddr* address) {
    curl_socket_t sockfd = CURL_SOCKET_BAD;

    /* restrict to IPv4 */
    if(purpose == CURLSOCKTYPE_IPCXN && address->family == AF_INET) {
        /* create a tcp socket object */
        boost::asio::ip::tcp::socket* tcp_socket =
            new boost::asio::ip::tcp::socket(http_manager_->thread_->io_service());

        /* open it and get the native handle*/
        boost::system::error_code code;
        tcp_socket->open(boost::asio::ip::tcp::v4(), code);

        if(!code) {
            sockfd = tcp_socket->native_handle();

            /* save it for monitoring */
            http_manager_->socket_list_[sockfd] = tcp_socket;
        }
    }

    return sockfd;
}
int HttpManager::close_socket(void* clientp, curl_socket_t sock) {
    auto iter = http_manager_->socket_list_.find(sock);
    if(iter != http_manager_->socket_list_.end()) {
        delete iter->second;
        http_manager_->socket_list_.erase(iter);
    }

    return 0;
}

size_t HttpManager::write_cb(void *buffer, size_t size, size_t count, void * stream) {
    CURL* curl = static_cast<CURL*>(stream);

    auto iter = http_manager_->callback_data_list_.find(curl);
    if (iter == http_manager_->callback_data_list_.end()) {
        return 0;
    }

    iter->second.buffer.append((char*)buffer, size*count);

    return size * count;
}

void HttpManager::check_multi_info() {
    CURLMsg *msg;
    int msgs_left;
    while((msg = curl_multi_info_read(http_manager_->curl_m_, &msgs_left))) {
        if(msg->msg == CURLMSG_DONE) {
            http_manager_->HttpRequestComplete(msg);
        }
    }
}

}