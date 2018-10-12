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

namespace reflect {

struct Member {
    std::string type;
    std::string name;
    void* value;
};

inline bool TypeIsInt8(const std::string& type) {  
    return (type == "int8_t" || type == "char");
}
inline bool TypeIsInt(const std::string& type) {
    return (type == "int" || type == "int32_t");
}
inline bool TypeIsInt64(const std::string& type) {
    return type == "int64_t";
}
inline bool TypeIsUInt8(const std::string& type) {    
    return type == "uint8_t";
}
inline bool TypeIsUInt(const std::string& type) {
    return (type == "uint" || type == "uint32_t");
}
inline bool TypeIsUInt64(const std::string& type) {
    return type == "uint64_t";
}
inline bool TypeIsFloat(const std::string& type) {
    return type == "float";
}
inline bool TypeIsDouble(const std::string& type) {
    return type == "double";
}
inline bool TypeIsBool(const std::string& type) {
    return type == "bool";
}
inline bool TypeIsString(const std::string& type) {
    return (type == "std::string" || type == "string");
}

}; // namespace reflect