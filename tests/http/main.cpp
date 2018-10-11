#include <http/http.h>
#include <jsoncpp/json/json.h>
#include <errors/errors.h>
#include <logs/logs.hpp>

class HttpTest : public http::HttpRequest::Delegate {
public:
    void OnHttpRequestComplete(std::shared_ptr<http::HttpRequest> request) override
    {
        std::cout << "OnRequestComplete" << std::endl;
        std::cout << "res:" << request->response() << std::endl;

        // Json::Value json_value;
        // Json::Reader json_reader;
        // json_reader.parse(request->response(), json_value);
        // Json::Value symbol_value = json_value["symbol_info"];
        // std::cout << json_value["test"].asString() << std::endl;
        // std::cout << symbol_value["symbol"].asString() << std::endl;
        // std::cout << symbol_value << std::endl;
    }

    void Start()
    {
        LOG_INFO("request start");
        request_.reset(new http::HttpRequest(
            http::HttpRequest::HttpMode::POST,
            "http://www.baidu.com", 
            this));
        request_->add_params("symbol", "btcusdt");
        START_HTTP_REQUEST(request_);
    }

    std::shared_ptr<http::HttpRequest> request_;
};

int main() {
    INIT_ERRORS_SIGNAL();
    HTTP_INIT();

    HttpTest http_test;
    http_test.Start();

    std::vector<HttpTest> http_test_list;
    for (size_t i = 0; i < 10000; i++) {
        http_test_list.push_back(http_test);
    }

    while (true) {
        for (size_t i = 0; i < http_test_list.size(); i++) {
            http_test_list[i].Start();
            usleep(100000);
        }       
    }

    return 0;
}