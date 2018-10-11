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

#include <iostream>
#include <string>
#include <base/base.h>

int main(int argc, char** argv) {
    std::cout << "md5:" << base::md5("test") << std::endl;
    std::cout << "sha1:" << base::sha1("test") << std::endl;
    std::cout << "sha224:" << base::sha224("test") << std::endl;
    std::cout << "sha256:" << base::sha256("test") << std::endl;
    std::cout << "sha384:" << base::sha384("test") << std::endl;
    std::cout << "sha512:" << base::sha512("test") << std::endl;

    auto output =  base::encode_aes("test", "123456");
    std::cout << base::decode_aes(output, "123456") << std::endl;

    std::string data = "0xb68788c83c2f1124578799e618c40c9467103160b68788c83c2f1124578799e618c40c9467103160";
    std::string public_key, private_key;
    std::string encode_data;
    std::string decode_data;
    base::new_rsa(1024, public_key, private_key);
    base::encode_rsa(data, public_key, encode_data);
    base::decode_rsa(encode_data, private_key, decode_data);
    std::cout << "encode_rsa:" << encode_data << std::endl;
    std::cout << "decode_rsa:" << decode_data << std::endl;

    std::string urlencode = base::encode_url("+-*/");
    std::cout << "url encode:" << urlencode << std::endl;
    std::cout << "url decode:" << base::decode_url(urlencode) << std::endl;

    return 0;
}