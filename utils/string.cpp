#include <utils/string.h>
#include <stdarg.h>

namespace utils {

std::string Map2UrlQuery(const std::map<std::string, std::string> params) {
    std::string str_params = "";
    for (auto iter = params.begin(); iter != params.end(); iter++) {
        if (str_params == "") {
            str_params += iter->first + "=" + iter->second;
        } else {
            str_params += "&" + iter->first + "=" + iter->second;
        }
    }

    return str_params;
}

std::string StringPrintf(const char* format,  ...)
{
    char buf[1024];
    char* p = buf;
    va_list args;
    va_start(args, format);
    vsprintf(p, format, args);
    va_end(args);
    return p;
}

int StringToInt(const std::string& str_value) {
    int value = 0;
    sscanf(str_value.c_str(), "%d", &value);
    return value;
}

int64_t StringToInt64(const std::string& str_value) {
    int64_t value = 0;
    sscanf(str_value.c_str(), "%ld", &value);
    return value;
}

}