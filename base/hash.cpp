#include <base/hash.h>

#include <iostream>
#include <string.h>
#include <logs/logs.hpp>

namespace base {

std::string md5(const std::string& data) {
    char tmp[3] = {0};
    char result[33] = {0};
    unsigned char md[16] = {0};

    MD5((const unsigned char *)data.c_str(), data.size(), md);

    for (size_t i = 0; i < 16; i++){
        sprintf(tmp, "%2.2x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

std::string sha256(const std::string& data) {
    char tmp[3] = {0};
    char result[65] = {0};
    unsigned char md[32] = {0};

	SHA256((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 32; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

std::string sha512(const std::string& data) {
    char tmp[3] = {0};
    char result[129] = {0};
    unsigned char md[64] = {0};

	SHA512((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 64; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

std::string encode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]) {
    size_t size = 0;
    if ((data.size() + 1) % AES_BLOCK_SIZE == 0) {
        size = data.size() + 1;
    } else {
        size = ((data.size()+1)/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
    }

    char key[AES_BLOCK_SIZE] = {0};
    strcpy(key, password);

    AES_KEY aes_key;
    if (AES_set_encrypt_key((const unsigned char*)key, 128, &aes_key) < 0) {
        LOG_ERROR("Unable to set encryption key in AES.");
        return "";
    }

    char iv[AES_BLOCK_SIZE] = {0};
    char* encrypt = new char[size];
    AES_cbc_encrypt((const unsigned char*)data.c_str(), (unsigned char*)encrypt, 
        size, &aes_key, (unsigned char*)iv, AES_ENCRYPT);

    std::string result(encrypt, size);
    delete []encrypt;

    return result;
}

std::string decode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]) {
    char key[AES_BLOCK_SIZE] = {0};
    strcpy(key, password);

    AES_KEY aes_key;
    if (AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key) < 0) {
        LOG_ERROR("Unable to set encryption key in AES.");
        return "";
    }

    char iv[AES_BLOCK_SIZE] = {0};
    char* decrypt = new char[data.size()];
    AES_cbc_encrypt((const unsigned char *)data.c_str(), (unsigned char *)decrypt, 
        data.size(), &aes_key, (unsigned char *)iv, AES_DECRYPT);

    std::string result(decrypt);
    delete []decrypt;

    return result;
}

}