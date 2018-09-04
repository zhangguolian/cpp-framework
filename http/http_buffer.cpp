#include <http/http_buffer.h>

#include <iostream>


namespace http {

    HttpBuffer::HttpBuffer(int size) 
                    : used_(0), size_(size) {
        buffer_ = new char[size];
    }
    HttpBuffer::~HttpBuffer() {
        delete[] buffer_;
        buffer_ = NULL;
        used_ = 0;
        size_ = 0;
    }

    char* HttpBuffer::Append(char* buffer, int size) {
        return NULL;
    }

    int HttpBuffer::size() {
        return size_;
    }
    int HttpBuffer::used() {
        return used_;
    }
    char* HttpBuffer::buffer() {
        return buffer_;
    }
    
}