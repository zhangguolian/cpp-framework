#pragma once

#include <string>
#include <openssl/sha.h>
#include <openssl/md5.h> 
#include <openssl/aes.h>

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

std::string url_encode(const std::string& data);
std::string url_decode(const std::string& data);

};