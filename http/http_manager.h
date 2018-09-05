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
    struct CallbackData 
    {
      CallbackData() : request_(NULL)
                     , buffer_(new HttpBuffer(DEFAULT_BUFFER_SIZE)) {}
      ~CallbackData() {
          if (buffer_ != NULL) {
              delete buffer_;
              buffer_ = NULL;
          }
      }

      HttpRequest* request_;
      HttpBuffer* buffer_;
    };

    typedef std::map<HttpRequest*, CURL*> REQUEST_LIST;
    typedef std::map<CURL*, CallbackData> CB_DATA_MAP;

    static HttpManager* GetInstance();

    void Start();
    void Cancel();

    void AddHttpRequest(HttpRequest* request);
    void CancelHttpRequest(HttpRequest* request);

private:
    HttpManager();
    ~HttpManager();

    int CurlSelect();
    void HttpRequestComplete(CURLMsg* msg);
    CURL* CreateCURL(HttpRequest* request);

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