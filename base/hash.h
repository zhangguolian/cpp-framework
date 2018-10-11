/*
 *
 * Copyright 2018 Guolian Zhang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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