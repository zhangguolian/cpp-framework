#include <http/http_manager.h>
#include <http/http_request.h>

class HttpTest : public http::HttpRequest::Delegate {
public:
    void OnHttpRequestComplete(http::HttpRequest* request) override
    {
        std::cout << "OnRequestComplete" << std::endl;
        std::cout << "res:" << request->response() << std::endl;
    }

    void Start()
    {
        request_ = new http::HttpRequest(
            http::HttpRequest::HttpMode::POST,
            "http://150.109.59.176/exchange/api/1.0/user/symbol/info", 
            this);
        request_->add_params("symbol", "btcusdt");
        request_->Start();
    }

    http::HttpRequest* request_;
};

int main() {
    http::HttpManager::GetInstance()->Start();

    HttpTest http_test;
    http_test.Start();

    while (true) {
        // HttpTest* http_test = new HttpTest();
        // http_test->Start();
        sleep(1);
    }

    return 0;
}