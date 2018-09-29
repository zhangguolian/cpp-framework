#include <iostream>
#include <string>
#include <base/base.h>
#include <boost/random.hpp>

int main(int argc, char** argv) {
    std::cout << base::StringPrintf("test%d, test%s", 1, "2") << std::endl;
    std::cout << "md5:" << base::md5("test") << std::endl;
    std::cout << "sha1:" << base::sha1("test") << std::endl;
    std::cout << "sha224:" << base::sha224("test") << std::endl;
    std::cout << "sha256:" << base::sha256("test") << std::endl;
    std::cout << "sha384:" << base::sha384("test") << std::endl;
    std::cout << "sha512:" << base::sha512("test") << std::endl;
    
    // std::string eaes = base::encode_aes("test", "123456");
    // std::cout << eaes << std::endl;
    // std::string daes = base::decode_aes(eaes, "123456");
    // std::cout << daes << std::endl;

    auto output =  base::encode_aes("test333333333333333333333333333333333333", "123456");
    std::cout << base::decode_aes(output, "123456") << std::endl;

    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0.0, 1.0) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;
    std::cout << base::Rand(0, 100) << std::endl;

    std::string data = "test123123123123123123";
    std::string public_key, private_key;
    std::string encode_data;
    std::string decode_data;
    base::new_rsa(512, public_key, private_key);
    base::encode_rsa(data, public_key, encode_data);
    base::decode_rsa(encode_data, private_key, decode_data);
    std::cout << "encode_rsa:" << encode_data << std::endl;
    std::cout << "decode_rsa:" << decode_data << std::endl;

    std::string urlencode = base::url_encode("+8615818225465");
    std::cout << "url encode:" << urlencode << std::endl;
    std::cout << "url decode:" << base::url_decode(urlencode) << std::endl;

    return 0;
}