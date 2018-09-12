#pragma once 

#include <string>
#include <map>
#include <curl/curl.h>
#include <boost/thread/mutex.hpp>

#include <http/http_buffer.h>

namespace http {

#define DEFAULT_BUFFER_SIZE 1024 * 1024

class HttpRequest;

class HttpManager {
public:
    struct CallbackData {
        CallbackData() : buffer_(new HttpBuffer(DEFAULT_BUFFER_SIZE)) {}
        ~CallbackData() {
            if (buffer_ != NULL) {
                delete buffer_;
                buffer_ = NULL;
            }
        }

        HttpBuffer* buffer_;
        std::shared_ptr<http::HttpRequest> request_;
    };

    struct CURLData {
        CURLData() : curl_(NULL)
                   , headers_(NULL) {}
        ~CURLData() {
            if (curl_ != NULL) {
                curl_easy_cleanup(curl_);
                curl_ = NULL;
            }

            if (headers_ != NULL) {
                curl_slist_free_all(headers_);
                headers_ = NULL;
            }
        }

        CURL* curl_;
        struct curl_slist* headers_;
        std::string post_data_;
    };

    typedef std::map<std::shared_ptr<HttpRequest>, std::unique_ptr<CURLData>> REQUEST_LIST;
    typedef std::map<CURL*, CallbackData> CB_DATA_MAP;

    static HttpManager* GetInstance();

    void Start();
    void Cancel();

    void AddHttpRequest(std::shared_ptr<HttpRequest> request);
    void CancelHttpRequest(std::shared_ptr<HttpRequest> request);

private:
    HttpManager();
    ~HttpManager();

    int CurlSelect();
    void HttpRequestComplete(CURLMsg* msg);
    CURLData* CreateCURLData(std::shared_ptr<HttpRequest> request);

    void WorkerThread();
    static size_t WriteCallback(void *buffer, size_t size, size_t count, void * stream);

private:
    bool is_running_;
    CURLM* curl_m_;
    boost::mutex mutex_;
    REQUEST_LIST request_list_;
    CB_DATA_MAP callback_data_list_;

    static HttpManager* http_manager_;
};

};