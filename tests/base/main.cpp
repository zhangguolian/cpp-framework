#include <iostream>
#include <string>
#include <base/base.h>
#include <boost/random.hpp>

int main(int argc, char** argv) {
    std::cout << base::StringPrintf("test%d, test%s", 1, "2") << std::endl;
    std::cout << base::md5("test") << std::endl;
    std::cout << base::sha256("test") << std::endl;
    
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

    return 0;
}