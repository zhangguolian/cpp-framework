#include <utils/hash.h>

#include <iostream>
#include <string.h>

namespace utils {

std::string sha256(const std::string& input) {
    unsigned char md[33] = {0};
	SHA256((const unsigned char *)input.c_str(), input.size(), md);
    
	int i = 0;
	char buf[65] = {0};
    char tmp[3] = {0};
    for(i = 0; i < 32; i++ ) {
        sprintf(tmp,"%02x", md[i]);
        strcat(buf, tmp);
    }

    return buf;
}

}