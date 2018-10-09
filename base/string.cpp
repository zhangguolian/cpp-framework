#include <base/string.h>
#include <stdarg.h>

namespace base {

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

int StringToInt(const std::string& data) {
    int result = 0;
    sscanf(data.c_str(), "%d", &result);
    return result;
}

int64_t StringToInt64(const std::string& data) {
    int64_t result = 0;
    sscanf(data.c_str(), "%ld", &result);
    return result;
}

uint StringToUInt(const std::string& data) {
    uint result = 0;
    sscanf(data.c_str(), "%u", &result);
    return result;
}

uint64_t StringToUInt64(const std::string& data) {
    uint64_t result = 0;
    sscanf(data.c_str(), "%lu", &result);
    return result;
}

float StringToFloat(const std::string& data) {
    float result = 0.0;
    sscanf(data.c_str(), "%f", &result);
    return result;
}

double StringToDouble(const std::string& data) {
    double result = 0.0;
    sscanf(data.c_str(), "%lf", &result);
    return result;
}

bool StringToBool(const std::string& data) {
    if (data == "true") {
        return true;
    }
    return false;
}

}