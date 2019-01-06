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
#include <reflect/reflect.h>
#include <jsoncpp/json/json.h>
#include <logs/logs.hpp>

namespace base {

inline Json::Value JsonMarShal(void* data) {
    Json::Value json_value;

    auto members = REFLECT_MEMBERS(data);
    for (size_t i = 0; i < members.size(); i++) {
        if (reflect::TypeIsInt8(members[i].type)) {
            json_value[members[i].name] = *(int8_t*)members[i].value;
        } else if (reflect::TypeIsInt(members[i].type)) {
            json_value[members[i].name] = *(int*)members[i].value;
        } else if (reflect::TypeIsInt64(members[i].type)) {
            json_value[members[i].name] = Json::Int64(*(int64_t*)members[i].value);
        } else if (reflect::TypeIsUInt8(members[i].type)) {
            json_value[members[i].name] = *(uint8_t*)members[i].value;
        } else if (reflect::TypeIsUInt(members[i].type)) {
            json_value[members[i].name] = *(uint32_t*)members[i].value;
        } else if (reflect::TypeIsUInt64(members[i].type)) {
            json_value[members[i].name] = Json::UInt64(*(uint64_t*)members[i].value);
        } else if (reflect::TypeIsFloat(members[i].type)) {
            json_value[members[i].name] = *(float*)members[i].value;
        } else if (reflect::TypeIsDouble(members[i].type)) {
            json_value[members[i].name] = *(double*)members[i].value;
        } else if (reflect::TypeIsBool(members[i].type)) {
            json_value[members[i].name] = *(bool*)members[i].value;
        } else if (reflect::TypeIsString(members[i].type)) {
            json_value[members[i].name] = *(std::string*)members[i].value;
        } else if (reflect::TypeIsArray(members[i].type)) {
            reflect::Array* array = static_cast<reflect::Array*>(members[i].value);
            if (array != NULL) {
                for (size_t j = 0; j < array->size(); j++) {
                    json_value[members[i].name].append(JsonMarShal(array->index(j)));
                }
            }
        } else {
            json_value[members[i].name] = JsonMarShal(members[i].value);
        }    
    }

    return json_value;
}
template<class T>
std::string JsonMarShal(const T& data) {
    T data1;
    data1 = data;
    return JsonMarShal((void*)&data1).toStyledString();
}
template<class T>
std::string JsonMarShal(const std::vector<T>& data_list) {
    T data;
    Json::Value json_value;
    for (size_t i = 0; i < data_list.size(); i++) {
        data = data_list[i];
        json_value.append(JsonMarShal((void*)&data));
    }
    return json_value.toStyledString();
}

inline void JsonUnmarshal(const Json::Value& json_value,
                          void* result) {
    auto members = REFLECT_MEMBERS(result);

    try {
        for (size_t i = 0; i < members.size(); i++) {
            if (reflect::TypeIsInt8(members[i].type)) {
                *(int8_t*)members[i].value = (int8_t)json_value[members[i].name].asInt();
            } else if (reflect::TypeIsInt(members[i].type)) {
                *(int*)members[i].value = json_value[members[i].name].asInt();
            } else if (reflect::TypeIsInt64(members[i].type)) {
                *(int64_t*)members[i].value = json_value[members[i].name].asInt64();
            } else if (reflect::TypeIsUInt8(members[i].type)) {
                *(uint8_t*)members[i].value = (uint8_t)json_value[members[i].name].asUInt();
            } else if (reflect::TypeIsUInt(members[i].type)) {
                *(uint32_t*)members[i].value = json_value[members[i].name].asUInt();
            } else if (reflect::TypeIsUInt64(members[i].type)) {
                *(uint64_t*)members[i].value = json_value[members[i].name].asUInt64();
            } else if (reflect::TypeIsFloat(members[i].type)) {
                *(float*)members[i].value = json_value[members[i].name].asFloat();
            } else if (reflect::TypeIsDouble(members[i].type)) {
                *(double*)members[i].value = json_value[members[i].name].asDouble();
            } else if (reflect::TypeIsBool(members[i].type)) {
                *(bool*)members[i].value = json_value[members[i].name].asBool();
            } else if (reflect::TypeIsString(members[i].type)) {
                *(std::string*)members[i].value = json_value[members[i].name].asString();
            } else if (reflect::TypeIsArray(members[i].type)) {
                reflect::Array* array = static_cast<reflect::Array*>(members[i].value);
                if (array != NULL && json_value[members[i].name].isArray()) {
                    array->clear();
                    for (int j = 0; j < int(json_value[members[i].name].size()); j++) {
                        JsonUnmarshal(json_value[members[i].name][j], array->add());
                    }
                }
            } else {
                JsonUnmarshal(json_value[members[i].name], members[i].value);
            }    
        }
    } catch(...) {
        LOG_ERROR("JsonUnmarshal json error.");
        return;
    }              
        
    return;
}
template<class T>
void JsonUnmarshal(const Json::Value& json_value,
                   T& result) {
    JsonUnmarshal(json_value, (void*)&result);
}
template<class T>
void JsonUnmarshal(const Json::Value& json_value,
                   std::vector<T>& results) {
    for (int i = 0; i < int(json_value.size()); i++) {
        T result;
        JsonUnmarshal(json_value[i], (void*)&result);
        results.push_back(result);
    }
}
template<class T>
bool JsonUnmarshal(const std::string& data,
                   T& result) {
    Json::Value json_value;
    Json::Reader json_reader; 
    try {
        if (!json_reader.parse(data, json_value)) {
            LOG_ERROR("JsonUnmarshal json_reader.parse fail.");
            return false;  
        }

        JsonUnmarshal(json_value, (void*)&result);
    } catch(...) {
        LOG_ERROR("JsonUnmarshal json error, data:%s.", data.c_str());
        return false;
    }              
        
    return true;
}
template<class T>
bool JsonUnmarshal(const std::string& data,
                   std::vector<T>& results) {
    Json::Value json_value;
    Json::Reader json_reader; 
    try {
        if (!json_reader.parse(data, json_value)) {
            LOG_ERROR("JsonUnmarshal json_reader.parse fail.");
            return false;  
        }

        if (!json_value.isArray()) {
            return false;
        }

        for (int i = 0; i < int(json_value.size()); i++) {
            T result;
            JsonUnmarshal(json_value[i], (void*)&result);
            results.push_back(result);
        }
    } catch(...) {
        LOG_ERROR("JsonUnmarshal json error, data:%s.", data.c_str());
        return false;
    }              
        
    return true;
}

} // namespace base
