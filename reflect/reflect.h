#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <reflect/member.hpp>

namespace reflect {

class Reflect {
public:
    static Reflect* GetInstance();

    void add_member(void* obj,
                    void* value,
                    const std::string& type,
                    const std::string& name);
    void remove_member(void* obj);
    const std::vector<Member>& member_list(void* obj);
private:
    Reflect();
    ~Reflect();

private:
    std::map<void*, std::vector<Member>> member_list_;
    static Reflect* reflect_;
};

};

#define REFLECT_REGIST(obj, type, name)\
    reflect::Reflect::GetInstance()->add_member((void*)obj, (void*)&name, #type, #name);

#define REFLECT_UNREGIST(obj)\
    reflect::Reflect::GetInstance()->remove_member((void*)obj);
  
#define REFLECT_MEMBERS(obj)\
    reflect::Reflect::GetInstance()->member_list((void*)obj);
    
