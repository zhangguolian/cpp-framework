#pragma once

#include <string>
#include <openssl/sha.h>
#include <openssl/md5.h> 
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

namespace base {

std::string md5(const std::string& data);
std::string sha1(const std::string& data);
std::string sha224(const std::string& data);
std::string sha256(const std::string& data);
std::string sha384(const std::string& data);
std::string sha512(const std::string& data);

std::string encode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]);
std::string decode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]);

bool new_rsa(int bits,
             std::string& public_key, 
             std::string& private_key);
bool encode_rsa(const std::string& data,
                const std::string& public_key,
                std::string& result);
bool decode_rsa(const std::string& data, 
                const std::string& private_key,
                std::string& result);

std::string encode_url(const std::string& data);
std::string decode_url(const std::string& data);

};