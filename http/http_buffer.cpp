#include <http/http_buffer.h>

#include <iostream>
#include <string.h>


namespace http {

HttpBuffer::HttpBuffer(int size) 
            : size_(size)
            , used_(0) {
    buffer_ = new char[size];
}
HttpBuffer::~HttpBuffer() {
    delete[] buffer_;
    buffer_ = NULL;
    used_ = 0;
    size_ = 0;
}

char* HttpBuffer::Append(char* buffer, int size) {
    if (size_ - used_ <= size) {
        char* new_buffer = new char[size_*2+size];
        memcpy(new_buffer, buffer_, used_);
        delete[] buffer_;
        buffer_ = new_buffer;
        size_ *= 2;
    }

    memcpy(buffer_+used_, buffer, size);
    used_ += size;

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