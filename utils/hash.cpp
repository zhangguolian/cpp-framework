#include <utils/hash.h>

#include <iostream>
#include <string.h>

namespace utils {

std::string sha256(const std::string& input) {
    std::string encodedStr;
    std::string encodedHexStr;

    // 调用sha256哈希    
    unsigned char mdStr[33] = {0};  
    SHA256((const unsigned char *)input.c_str(), input.size(), mdStr);  

    // 哈希后的字符串    
    encodedStr = std::string((const char *)mdStr);  
    // 哈希后的十六进制串 32字节    
    char buf[65] = {0};  
    char tmp[3] = {0};  
    for (int i = 0; i < 32; i++)  
    {  
        sprintf(tmp, "%02x", mdStr[i]);  
        strcat(buf, tmp);  
    }  
    buf[32] = '\0'; // 后面都是0，从32字节截断    
    encodedHexStr = std::string(buf);

    printf("%s\n", encodedStr.c_str());
    printf("%s\n", encodedHexStr.c_str());

    return encodedHexStr;
}

}