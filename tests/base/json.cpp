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

#include <iostream>
#include <base/base.h>

struct JsonData {
    // Define reflect params
    REFLECT_DEFINE(int, data1);
    REFLECT_DEFINE(std::string, data2);
};

struct JsonTest {
    JsonTest() {
        a = 1;
        b = 2;
        c = 3;
        d = 4;
        e = 5;
        f = 6;
        g = 0.1;
        h = 0.2;
        i = true;
        j = "test";
        data.data1 = 2;
        data.data2 = "json_data";
    }

    // Define reflect params
    REFLECT_DEFINE(int8_t, a);
    REFLECT_DEFINE(int, b);
    REFLECT_DEFINE(int64_t, c);
    REFLECT_DEFINE(uint8_t, d);
    REFLECT_DEFINE(uint, e);
    REFLECT_DEFINE(uint64_t, f);
    REFLECT_DEFINE(float, g);
    REFLECT_DEFINE(double, h);
    REFLECT_DEFINE(bool, i);
    REFLECT_DEFINE(std::string, j);
    REFLECT_DEFINE(JsonData, data);
};

int main() {
    // Json serialization of json_test
    JsonTest json_test;
    std::string json_marshal = base::JsonMarShal(json_test);
    std::cout << "JsonMarshal:" << json_marshal << std::endl;

    // Parse the json string into json_test1
    JsonTest json_test1;
    if (!base::JsonUnmarshal(json_marshal, json_test1)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
        return -1;
    } else {
        std::cout << "JsonUnmarshal:" 
                  << json_test1.a << "," 
                  << json_test1.b << ","
                  << json_test1.c << "," 
                  << json_test1.d << "," 
                  << json_test1.e << "," 
                  << json_test1.f << "," 
                  << json_test1.g << "," 
                  << json_test1.h << "," 
                  << json_test1.i << "," 
                  << json_test1.j << "," 
                  << json_test1.data.data1 << ","
                  << json_test1.data.data2 << ","
                  << std::endl;
        json_test1.a += 1;
    }

    // Json arrays serialization for json_test_list
    std::vector<JsonTest> json_test_list;
    json_test_list.push_back(json_test);
    json_test_list.push_back(json_test1);
    std::cout << base::JsonMarShal(json_test_list) << std::endl;

    // Parse the json arrays string into json_test_list1
    std::vector<JsonTest> json_test_list1;
    if (!base::JsonUnmarshal(base::JsonMarShal(json_test_list), json_test_list1)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
    } else {
        std::cout << base::JsonMarShal(json_test_list1) << std::endl;
    }

    return 0;
}