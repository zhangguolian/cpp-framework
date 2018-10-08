#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <reflect/member.hpp>

namespace reflect {

template<class T>
class Reflect {
public:
    static Reflect* GetInstance() {
        if (reflect_ == NULL) {
            reflect_ = new Reflect();
        }

        return reflect_;
    }

    void add_member(void* obj,
                    void* value,
                    const std::string& type,
                    const std::string& name) {
        Member member;
        member.type = type;
        member.name = name;
        member.value = value;
        member_list_[obj].push_back(member);
    }
    void remove_member(void* obj) {
        member_list_.erase(obj);
    }
    const std::vector<Member>& member_list(void* obj) {
        return member_list_[obj];
    }

private:
    Reflect() {}
    ~Reflect() {}

private:
    std::map<void*, std::vector<Member>> member_list_;
    static Reflect<T>* reflect_;
};

template<class T>
Reflect<T>* Reflect<T>::reflect_ = NULL;

};

#define REFLECT_REGIST(T, obj, type, name, value)\
    reflect::Reflect<T>::GetInstance()->add_member((void*)obj, (void*)value, #type, #name);

#define REFLECT_UNREGIST(T, obj)\
    reflect::Reflect<T>::GetInstance()->remove_member((void*)obj);
  
#define REFLECH_MEMBERS(T, obj)\
    reflect::Reflect<T>::GetInstance()->member_list((void*)obj);
    
