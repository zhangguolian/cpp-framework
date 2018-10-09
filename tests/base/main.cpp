#include <iostream>
#include <string>
#include <base/base.h>
#include <boost/random.hpp>

struct JsonTest {
    JsonTest() {
        REFLECT_REGIST(JsonTest, this, int, a, &a);
        REFLECT_REGIST(JsonTest, this, bool, b, &b);
        REFLECT_REGIST(JsonTest, this, std::string, c, &c);
    }
    ~JsonTest() {
        REFLECT_UNREGIST(JsonTest, this);
    }

    int a;
    bool b;
    std::string c;
};


int main(int argc, char** argv) {
    std::cout << base::StringPrintf("test%d, test%s", 1, "2") << std::endl;
    std::cout << base::StringToInt("1") << std::endl;
    std::cout << base::StringToInt64("2") << std::endl;
    std::cout << base::StringToUInt("3") << std::endl;
    std::cout << base::StringToUInt64("4") << std::endl;
    std::cout << base::StringToFloat("5.0") << std::endl;
    std::cout << base::StringToDouble("6.0") << std::endl;
    std::cout << base::StringToBool("true") << std::endl;

    std::cout << "md5:" << base::md5("test") << std::endl;
    std::cout << "sha1:" << base::sha1("test") << std::endl;
    std::cout << "sha224:" << base::sha224("test") << std::endl;
    std::cout << "sha256:" << base::sha256("test") << std::endl;
    std::cout << "sha384:" << base::sha384("test") << std::endl;
    std::cout << "sha512:" << base::sha512("test") << std::endl;

    auto output =  base::encode_aes("test333333333333333333333333333333333333", "123456");
    std::cout << base::decode_aes(output, "123456") << std::endl;

    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;

    std::string data = "0xb68788c83c2f1124578799e618c40c9467103160b68788c83c2f1124578799e618c40c9467103160";
    std::string public_key, private_key;
    std::string encode_data;
    std::string decode_data;
    base::new_rsa(1024, public_key, private_key);
    base::encode_rsa(data, public_key, encode_data);
    base::decode_rsa(encode_data, private_key, decode_data);
    std::cout << "encode_rsa:" << encode_data << std::endl;
    std::cout << "decode_rsa:" << decode_data << std::endl;

    std::string urlencode = base::encode_url("+8615818225465");
    std::cout << "url encode:" << urlencode << std::endl;
    std::cout << "url decode:" << base::decode_url(urlencode) << std::endl;

    JsonTest json_test;
    json_test.a = 1;
    json_test.b = true;
    json_test.c = "json_test";
    std::string json_marshal = base::JsonMarshal(json_test);
    std::cout << "JsonMarshal:" << json_marshal << std::endl;
    json_test.a = 0;
    json_test.b = false;
    json_test.c = "";
    if (!base::JsonUnmarshal(json_marshal, json_test)) {
        std::cout << "JsonUnmarshal fail" << std::endl;
    } else {
        std::cout << "JsonUnmarshal:" 
                  << json_test.a << "," 
                  << json_test.b << ","
                  << json_test.c << std::endl;
    }


    return 0;
}