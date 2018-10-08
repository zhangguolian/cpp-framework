#pragma once 

#include <string>
#include <reflect/reflect.hpp>
#include <jsoncpp/json/json.h>
#include <logs/logs.hpp>

namespace base {

template<class T>
std::string JsonMarshal(const T& data) {
    Json::Value json_value;

    auto members = REFLECT_MEMBERS(T, &data);
    for (size_t i = 0; i < members.size(); i++) {
        if (reflect::TypeIsInt(members[i].type)) {
            json_value[members[i].name] = *(int*)members[i].value;
        } else if (reflect::TypeIsInt64(members[i].type)) {
            json_value[members[i].name] = Json::Int64(*(int64_t*)members[i].value);
        } else if (reflect::TypeIsUInt(members[i].type)) {
            json_value[members[i].name] = *(uint*)members[i].value;
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
        } else {
            LOG_ERROR("JsonMarshal unknow type %s", members[i].type.c_str());
        }    
    }

    return json_value.toStyledString();
}

template<class T>
bool JsonUnmarshal(const std::string& data,
                   T& result) {
    auto members = REFLECT_MEMBERS(T, &result);

    Json::Value json_value;
    Json::Reader json_reader; 
    try {
        if (!json_reader.parse(data, json_value)) {
            LOG_ERROR("JsonUnmarshal json_reader.parse fail.");
            return false;  
        }

        for (size_t i = 0; i < members.size(); i++) {
            if (reflect::TypeIsInt(members[i].type)) {
                *(int*)members[i].value = json_value[members[i].name].asInt();
            } else if (reflect::TypeIsInt64(members[i].type)) {
                *(int64_t*)members[i].value = json_value[members[i].name].asInt64();
            } else if (reflect::TypeIsUInt(members[i].type)) {
                *(uint*)members[i].value = json_value[members[i].name].asUInt();
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
            } else {
                LOG_ERROR("JsonMarshal unknow type %s", members[i].type.c_str());
            }    
        }
    } catch(...) {
        LOG_ERROR("JsonUnmarshal json error, data:%s.", data.c_str());
        return false;
    }              
        
    return true;
}

}
