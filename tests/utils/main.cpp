#include <iostream>
#include <string>
#include <utils/utils.h>

int main(int argc, char** argv) {
    std::cout << utils::StringPrintf("test%d, test%s", 1, "2") << std::endl;
    std::cout << utils::md5("test") << std::endl;
    std::cout << utils::sha256("test") << std::endl;
    
    // std::string eaes = utils::encode_aes("test", "123456");
    // std::cout << eaes << std::endl;
    // std::string daes = utils::decode_aes(eaes, "123456");
    // std::cout << daes << std::endl;

    auto output =  utils::encode_aes("test", "123456");
    std::cout << utils::decode_aes(output, "123456") << std::endl;

    return 0;
}