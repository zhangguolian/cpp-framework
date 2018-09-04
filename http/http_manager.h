#pragma once 

#include <string>
#include <map>

namespace http {

enum HttpMode{
    HTTP_GET = 0,
    HTTP_POST,
};

class HttpManager {
public:
    // struct CallbackData 
    // {
    //   CallbackData();
    //   CallbackData(CURLRequest* request);
    //   ~CallbackData();

    //   CURLRequest* request_;
    //   CURLBuffer* buffer_;
    // };

private:

};

};