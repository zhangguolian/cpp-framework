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
        http::HttpRequest  *request = new http::HttpRequest(
            http::HttpRequest::HttpMode::GET,
            "http://www.baidu.com", 
            this);
        request->Start();
    }
};

int main() {
    http::HttpManager::GetInstance()->Start();

    HttpTest http_test;
    http_test.Start();

    while (true) {
        
    }

    return 0;
}