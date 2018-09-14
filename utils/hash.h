#pragma once

#include <string>
#include <openssl/sha.h>

namespace utils {

std::string sha256(const std::string& input);

};