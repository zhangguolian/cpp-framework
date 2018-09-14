#pragma once

#include <string>

namespace utils {

std::string md5(const std::string& data);
std::string sha256(const std::string& data);
unsigned char* encode_aes(const std::string& data, 
                          const std::string& password);
std::string decode_aes(unsigned char* data, 
                       const std::string& password);

};