#include <http/http_manager.h>

#include <curl/easy.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <http/http_request.h>
#include <base/base.h>

namespace http {

HttpManager* HttpManager::http_manager_ = NULL;

HttpManager::HttpManager()
            : is_running_(false)
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

    is_running_ = true;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_m_ = curl_multi_init();
    
    boost::thread work_thread(boost::bind(
        &HttpManager::WorkerThread, this));
}
void HttpManager::Cancel() {
    if (!is_running_) {
        return;  
    }

    mutex_.lock();
    for (auto iter = callback_data_list_.begin(); iter != callback_data_list_.end(); iter++) {
        curl_multi_remove_handle(curl_m_, iter->first);
        curl_easy_cleanup(iter->first);
    }
    curl_multi_cleanup(curl_m_);
    curl_m_ = NULL;
    request_list_.clear();
    callback_data_list_.clear();
    mutex_.unlock();
}

void HttpManager::AddHttpRequest(std::shared_ptr<HttpRequest> request) {
    mutex_.lock();
    if (request == NULL || request_list_.find(request) != request_list_.end()) {
        mutex_.unlock();
        return;
    }
    mutex_.unlock();

    CURLData* curl_data = CreateCURLData(request);

    mutex_.lock();
    request_list_[request].reset(curl_data);
    callback_data_list_[curl_data->curl_].request_ = request;
    curl_multi_add_handle(curl_m_, curl_data->curl_);
    mutex_.unlock();
}
void HttpManager::CancelHttpRequest(std::shared_ptr<HttpRequest> request) {
    mutex_.lock();

    auto iter = request_list_.find(request);
    if (iter == request_list_.end()) {
        mutex_.lock();
        return;
    }

    curl_multi_remove_handle(curl_m_, iter->second->curl_);
    curl_easy_cleanup(iter->second->curl_);
    callback_data_list_.erase(iter->second->curl_);
    request_list_.erase(request);

    mutex_.unlock();

    return;
}

HttpManager::CURLData* HttpManager::CreateCURLData(std::shared_ptr<HttpRequest> request) {
    CURLData* curl_data = new CURLData();
    curl_data->curl_ = curl_easy_init();

    std::string url = request->url();
    if (!request->params().empty()) {
        if (request->http_mode() == HttpRequest::HttpMode::GET) {
            url += "?" + base::Map2UrlQuery(request->params());
        } else {
            curl_data->headers_ = curl_slist_append(curl_data->headers_, "Content-Type: application/x-www-form-urlencoded");
            curl_data->headers_ = curl_slist_append(curl_data->headers_, "Accept-Language: zh-cn");
            curl_data->post_data_ = base::Map2UrlQuery(request->params());
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
    curl_easy_setopt(curl_data->curl_, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl_data->curl_, CURLOPT_MAXREDIRS, 5);
    curl_easy_setopt(curl_data->curl_, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl_data->curl_, CURLOPT_WRITEFUNCTION, HttpManager::WriteCallback);
    curl_easy_setopt(curl_data->curl_, CURLOPT_WRITEDATA, curl_data->curl_);

    return curl_data;
}

int HttpManager::CurlSelect() {
    int ret = 0;

    struct timeval timeout_tv;
    fd_set  fd_read;
    fd_set  fd_write;
    fd_set  fd_except;
    int     max_fd = -1;

    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_except);

    timeout_tv.tv_sec = 0;
    timeout_tv.tv_usec = 500 * 1000;

    long curl_timeo = -1;
    ret = curl_multi_timeout(curl_m_, &curl_timeo); // curl_timeo ��λ�Ǻ���
    if (curl_timeo >= 0) {
        timeout_tv.tv_sec = curl_timeo / 1000;
        if (timeout_tv.tv_sec > 1)
            timeout_tv.tv_sec = 1;
        else
            timeout_tv.tv_usec = (curl_timeo % 1000) * 1000;
    }

    curl_multi_fdset(curl_m_, &fd_read, &fd_write, &fd_except, &max_fd);

    /**
    * When max_fd returns with -1,
    * you need to wait a while and then proceed and call curl_multi_perform anyway.
    * How long to wait? I would suggest 100 milliseconds at least,
    * but you may want to test it out in your own particular conditions to find a suitable value.
    */
    if (-1 == max_fd) {
        if (curl_timeo > 1000)
        curl_timeo = 1000;

        return -2;
    }

    int ret_code = ::select(max_fd + 1, &fd_read, &fd_write, &fd_except, &timeout_tv);
    switch (ret_code) {
    case -1:
        /* select error */
        ret = -1;
        break;
    case 0:
        /* select timeout */
    default:
        /* one or more of curl's file descriptors say there's data to read or write*/
        ret = 0;
        break;
    }

    return ret;
}

void HttpManager::HttpRequestComplete(CURLMsg* msg) {
    mutex_.lock();

    if (!msg || !msg->easy_handle) {
        mutex_.unlock();
        return;
    }

    auto iter = callback_data_list_.find(msg->easy_handle);
    if (iter == callback_data_list_.end()) {
        mutex_.unlock();
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
        iter->second.request_->set_status(HttpRequest::Status::SUCCESS);
        iter->second.request_->set_response(std::string(iter->second.buffer_->buffer(), iter->second.buffer_->used()));
    } else {
        iter->second.request_->set_status(HttpRequest::Status::FAILED);
        iter->second.request_->set_http_code(http_code);
    }

    iter->second.request_->delegate()->OnHttpRequestComplete(iter->second.request_);

    request_list_.erase(iter->second.request_);
    callback_data_list_.erase(msg->easy_handle);
    curl_multi_remove_handle(curl_m_, msg->easy_handle);

    mutex_.unlock();

    return;
}

void HttpManager::WorkerThread() {
    HttpManager *http_manger = HttpManager::GetInstance();

    int running_handles = 0;
    while (http_manger->is_running_) {
      int ret_val = http_manger->CurlSelect();
      if (-2 == ret_val) {
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(http_manger->curl_m_, &running_handles)) { 
          ;
        }
      }
      else if (-1 == ret_val) {
        continue;
      }
      else {
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(http_manger->curl_m_, &running_handles)) {
          ;
        }
      }

      int msgs_left = 0;
      CURLMsg * msg = curl_multi_info_read(http_manger->curl_m_, &msgs_left);
      while (msg) {
        if (CURLMSG_DONE == msg->msg) {
            http_manger->HttpRequestComplete(msg);
        }

        msg = curl_multi_info_read(http_manger->curl_m_, &msgs_left);
      }
    }

    return;
}

size_t HttpManager::WriteCallback(void *buffer, size_t size, size_t count, void * stream) {
    CURL* curl = static_cast<CURL*>(stream);

    HttpManager* http_manager = HttpManager::GetInstance();

    http_manager->mutex_.lock();

    auto iter = http_manager->callback_data_list_.find(curl);
    if (iter == http_manager->callback_data_list_.end()) {
        http_manager->mutex_.unlock();
        return 0;
    }

    iter->second.buffer_->Append((char*)buffer, size*count);

    http_manager->mutex_.unlock();

    return size * count;
}

}