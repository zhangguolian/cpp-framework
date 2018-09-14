#pragma once

#include <string>

namespace utils {

std::string md5(const std::string& data);
std::string sha256(const std::string& data);
unsigned char* encode_aes(const std::string& data, 
                          const char password[16]);
std::string decode_aes(unsigned char* data, 
                       const char password[16]);

};