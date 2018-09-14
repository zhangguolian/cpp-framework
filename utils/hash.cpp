#include <utils/hash.h>

#include <iostream>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h> 

namespace utils {

std::string md5(const std::string& input) {
    char tmp[3] = {0};
    char result[33] = {0};
    unsigned char md[16] = {0};

    MD5((const unsigned char *)input.c_str(), input.size(), md);

    for (size_t i = 0; i < 16; i++){
        sprintf(tmp, "%2.2x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

std::string sha256(const std::string& input) {
    char tmp[3] = {0};
    char result[65] = {0};
    unsigned char md[33] = {0};

	SHA256((const unsigned char *)input.c_str(), input.size(), md);

    for(size_t i = 0; i < 32; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

}