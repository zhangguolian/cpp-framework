#pragma once

namespace http {

class HttpBuffer
{
public:
    HttpBuffer(int size);
    ~HttpBuffer();

    char* Append(char* buffer, int size);

    int size();
    int used();
    char* buffer();

private:
    int size_;
    int used_;
    char* buffer_;
};

};