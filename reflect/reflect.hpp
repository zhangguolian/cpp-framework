#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace reflect {

struct Member {
    std::string type;
    std::string name;
};

bool TypeIsInt(const std::string& type) {
    if (type == "int" || type == "int32_t") {
        return true;
    }
    return false;
}
bool TypeIsInt64(const std::string& type) {
    if (type == "int64_t") {
        return true;
    }
    return false;
}
bool TypeIsUInt(const std::string& type) {
    if (type == "uint" || type == "uint32_t") {
        return true;
    }
    return false;
}
bool TypeIsUInt64(const std::string& type) {
    if (type == "uint64_t") {
        return true;
    }
    return false;
}
bool TypeIsFloat(const std::string& type) {
    if (type == "float") {
        return true;
    }
    return false;
}
bool TypeIsDouble(const std::string& type) {
    if (type == "double") {
        return true;
    }
    return false;
}
bool TypeIsBool(const std::string& type) {
    if (type == "bool") {
        return true;
    }
    return false;
}
bool TypeIsString(const std::string& type) {
    if (type == "std::string" || type == "string") {
        return true;
    }
    return false;
}

template<class T>
class Reflect {
public:
    static Reflect* GetInstance() {
        if (reflect_ == NULL) {
            reflect_ = new Reflect();
        }

        return reflect_;
    }

    void add_member(const std::string& type,
                    const std::string& name) {
        Member member;
        member.type = type;
        member.name = name;
        member_list_.push_back(member);
    }
    const std::vector<Member>& member_list() {
        return member_list_;
    }

private:
    Reflect() {

    }
    ~Reflect() {

    }

private:
    std::vector<Member> member_list_;
    static Reflect<T>* reflect_;
};

template<class T>
Reflect<T>* Reflect<T>::reflect_ = NULL;

};

#define REFLECT_REGIST(T, type, name)\
class ReflechTmp##T##name {\
public:\
    ReflechTmp##T##name() {\
        reflect::Reflect<T>::GetInstance()->add_member(#type, #name);\
    }\
};\
ReflechTmp##T##name g_reflech_##T##name;
  
#define REFLECH_MEMBERS(T)\
    reflect::Reflect<T>::GetInstance()->member_list();
    
