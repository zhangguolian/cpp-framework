/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once 

#include <iostream>

namespace reflect {

class Array {
public:
    Array() : size_(0) {}
    virtual ~Array() {}

    virtual void* index(size_t i) = 0;
    virtual void* add() = 0;
    size_t size() {
        return size_;
    }
    void clear() {
        size_ = 0;
    }

protected:
    size_t size_;
};

}

#define REFLECT_ARRAY_DEFINE(class_name, type)\
class class_name : public reflect::Array {\
public:\
    class_name() {\
        total_size_ = 256;\
        list_ = new type[total_size_];\
    }\
    class_name(const class_name& data) {\
        list_ = new type[data.total_size_];\
        size_ = data.size_;\
        total_size_ = data.total_size_;\
        for (size_t i = 0; i < size_; i++) {\
            list_[i] = data.list_[i];\
        }\
    }\
    ~class_name() {\
        if (list_) {\
            delete[] list_;\
            list_ = NULL;\
        }\
    }\
    void* index(size_t i) override {\
        return (void*)&list_[i];\
    }\
    void* add() override {\
        if (size_ == total_size_) {\
            reserve(total_size_ * 2);\
        }\
        return (void*)&list_[size_++];\
    }\
    void push_back(const type& data) {\
        if (size_ == total_size_) {\
            reserve(total_size_ * 2);\
        }\
        list_[size_++] = data;\
    }\
    type& operator[] (int i) {\
        return list_[i];\
    }\
    class_name& operator= (const class_name& data) {\
        if (this == &data) {\
            return *this;\
        }\
        if (list_ != NULL) {\
            delete[] list_;\
            list_ = NULL;\
        }\
        list_ = new type[data.total_size_];\
        size_ = data.size_;\
        total_size_ = data.total_size_;\
        for (size_t i = 0; i < size_; i++) {\
            list_[i] = data.list_[i];\
        }\
        return *this;\
    }\
private:\
    void reserve(size_t size) {\
        type* old = list_;\
        list_ = new type[size];\
        for (size_t i = 0; i < size_; i++) {\
            list_[i] = old[i];\
        }\
        total_size_ = size;\
        delete[] old;\
    }\
private:\
    type* list_;\
    size_t total_size_;\
};
