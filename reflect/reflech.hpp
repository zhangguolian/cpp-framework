#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace reflect {

struct Member {
    std::string type;
    std::string name;
};

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
    
