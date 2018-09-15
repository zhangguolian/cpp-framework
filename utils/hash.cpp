#include <utils/hash.h>

#include <iostream>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h> 
#include <openssl/aes.h>

namespace utils {

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
    unsigned char md[33] = {0};

	SHA256((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 32; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

unsigned char* encode_aes(const std::string& data, 
                          const char password[16]) {
    size_t encry_size = 0;
    if ((data.size() + 1) % AES_BLOCK_SIZE == 0) {
        encry_size = data.size() + 1;
    } else {
        encry_size = ((data.size()+1)/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
    }

    // Generate AES 128-bit key
    unsigned char key[AES_BLOCK_SIZE];
    for (size_t i=0; i < 16; ++i) {
        key[i] = 32 + i;
    }

    strcpy((char*)key, password);

    // Set encryption key
    unsigned char iv[AES_BLOCK_SIZE];
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }

    AES_KEY aes_key;
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        printf("Unable to set encryption key in AES\n");
        return NULL;
    }

    unsigned char* input_string = (unsigned char*)calloc(encry_size, sizeof(unsigned char));
    strncpy((char*)input_string, data.c_str(), data.size());
    unsigned char* encrypt_string = (unsigned char*)calloc(encry_size, sizeof(unsigned char)); 
    AES_cbc_encrypt(input_string, encrypt_string, encry_size, &aes_key, iv, AES_ENCRYPT);

    for (size_t i=0; i<encry_size; ++i) {
        printf("%x%x", (encrypt_string[i] >> 4) & 0xf, 
                encrypt_string[i] & 0xf);    
    }
    printf("\n");

    return encrypt_string;
}

std::string decode_aes(unsigned char* data, 
                       const char password[16]) {
    // Generate AES 128-bit key
    unsigned char key[AES_BLOCK_SIZE];
    for (size_t i=0; i < 16; ++i) {
        key[i] = 32 + i;
    }

    strcpy((char*)key, password);

    // Set encryption key
    unsigned char iv[AES_BLOCK_SIZE];
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = 0;
    }

    AES_KEY aes_key;
    if (AES_set_decrypt_key(key, 128, &aes_key) < 0) {
        printf("Unable to set encryption key in AES\n");
        return "";
    }

    unsigned char* decrypt_string = (unsigned char*)calloc(strlen((char*)data), sizeof(unsigned char)); 
    AES_cbc_encrypt(data, decrypt_string, strlen((char*)data), &aes_key, iv, 
            AES_DECRYPT);

    printf("%s\n", decrypt_string);

    return (char*)decrypt_string;
}

}