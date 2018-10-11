#pragma once 

#include <string>
#include <map>
#include <curl/curl.h>
#include <async/async.h>
#include <boost/thread/mutex.hpp>

namespace http {

class HttpRequest;

class HttpManager {
public:
    struct CallbackData {
        CallbackData() {}
        ~CallbackData() {}

        std::string buffer;
        std::shared_ptr<http::HttpRequest> request;
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
    typedef std::map<CURL*, CallbackData> CB_DATA_LIST;
    typedef std::map<curl_socket_t, boost::asio::ip::tcp::socket*> SOCKET_LIST;

    static HttpManager* GetInstance();

    void Start();
    void Cancel();

    void AddHttpRequest(std::shared_ptr<HttpRequest> request);
    void CancelHttpRequest(std::shared_ptr<HttpRequest> request);

private:
    HttpManager();
    ~HttpManager();

    void HttpRequestComplete(CURLMsg* msg);
    CURLData* CreateCURLData(std::shared_ptr<HttpRequest> request);

    static int multi_timer_cb(CURLM* multi, long timeout_ms);
    static void timer_cb();
    static int sock_cb(CURL* curl, curl_socket_t sock, int what, void* cbp, void* sockp);
    static void addsock(curl_socket_t sock, CURL* easy, int action);
    static void setsock(int* fdp, curl_socket_t sock, CURL* easy, int act, int oldact);
    static void remsock(int* f);
    static void event_cb(curl_socket_t s, int action, const boost::system::error_code& error, int* fdp);
    static curl_socket_t opensocket(void* clientp, curlsocktype purpose, struct curl_sockaddr* address);
    static int close_socket(void* clientp, curl_socket_t item);
    static size_t write_cb(void* buffer, size_t size, size_t count, void* stream);
    static void check_multi_info();

private:
    bool is_running_;
    int still_running_;
    CURLM* curl_m_;
    async::Timer timer_; 
    std::shared_ptr<async::Thread> thread_;
    REQUEST_LIST request_list_;
    CB_DATA_LIST callback_data_list_;
    SOCKET_LIST socket_list_;

    static HttpManager* http_manager_;
};

};