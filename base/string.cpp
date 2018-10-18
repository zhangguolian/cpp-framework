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

int8_t StringToInt8(const std::string& data) {
    int8_t result = 0;
    sscanf(data.c_str(), "%c", &result);
    return result;
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

uint8_t StringToUInt8(const std::string& data) {
    uint8_t result = 0;
    sscanf(data.c_str(), "%c", &result);
    return result;
}

uint32_t StringToUInt(const std::string& data) {
    uint32_t result = 0;
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

} // namespace base