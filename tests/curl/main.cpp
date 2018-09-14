#include <curl/curl.h>
#include <curl/easy.h>
#include <logs/logs.hpp>

int main() {
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        LOG_INFO("code:%d", res);
    }

    return 0;
}