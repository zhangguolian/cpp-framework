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

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <reflect/member.hpp>

namespace reflect {

// C++ reflection class.
// Parsing for json and sql members.
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

}; // namespace reflect

// Object registration, constructor call in class.
//
// Param obj is object pointer.
// Param type is the type of the member like int.
// Param name is the name of the member.
#define REFLECT_REGIST(obj, type, name)\
    reflect::Reflect::GetInstance()->add_member((void*)obj, (void*)&name, #type, #name);

// Object unregistration, destructor call in class.
//
// Param obj is object pointer.
#define REFLECT_UNREGIST(obj)\
    reflect::Reflect::GetInstance()->remove_member((void*)obj);

// Get the list of members of the object.
//
// Param obj is object pointer.  
// Return vector of member.
#define REFLECT_MEMBERS(obj)\
    reflect::Reflect::GetInstance()->member_list((void*)obj);
    
