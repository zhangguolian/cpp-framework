#include <iostream>
#include <json/json.hpp>

struct JsonData {
    JsonData() {
        REFLECT_REGIST(this, int, data1);
        REFLECT_REGIST(this, std::string, data2);
    }
    ~JsonData() {
        REFLECT_UNREGIST(this);
    }

    int data1;
    std::string data2;
};

struct JsonTest {
    JsonTest() {
        REFLECT_REGIST(this, int, a);
        REFLECT_REGIST(this, bool, b);
        REFLECT_REGIST(this, std::string, c);
        REFLECT_REGIST(this, JsonData, data);

        a = 1;
        b = true;
        c = "json_test";
        data.data1 = 2;
        data.data2 = "json_data";
    }
    ~JsonTest() {
        REFLECT_UNREGIST(this);
    }

    int a;
    bool b;
    std::string c;
    JsonData data;
};

int main() {
    JsonTest json_test;
    std::string json_marshal = json::JsonMarShal(json_test);
    std::cout << "JsonMarshal:" << json_marshal << std::endl;
    JsonTest json_test1;
    if (!json::JsonUnmarshal(json_marshal, json_test1)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
    } else {
        std::cout << "JsonUnmarshal:" 
                  << json_test1.a << "," 
                  << json_test1.b << ","
                  << json_test1.c << "," 
                  << json_test1.data.data1 << ","
                  << json_test1.data.data2 << ","
                  << std::endl;
    }

    json_test1.a += 1;
    std::vector<JsonTest> json_test_list;
    json_test_list.push_back(json_test);
    json_test_list.push_back(json_test1);
    std::cout << json::JsonMarShal(json_test_list) << std::endl;

    std::vector<JsonTest> json_test_list1;
    if (!json::JsonUnmarshal(json::JsonMarShal(json_test_list), json_test_list1)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
    } else {
        std::cout << json::JsonMarShal(json_test_list1) << std::endl;
    }

    return 0;
}