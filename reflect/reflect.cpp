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

#include <reflect/reflect.h>

namespace reflect {

Reflect* Reflect::reflect_ = NULL;

Reflect::Reflect() {

}
Reflect::~Reflect() {

}

Reflect* Reflect::GetInstance() {
    if (NULL == reflect_) {
        reflect_ = new Reflect();
    }

    return reflect_;
}

void Reflect::add_member(void* obj,
                         void* value,
                         const std::string& type,
                         const std::string& name) {
    Member member;
    member.type = type;
    member.name = name;
    member.value = value;
    member_list_[obj].push_back(member);
}
void Reflect::remove_member(void* obj) {
    member_list_.erase(obj);
}
const std::vector<Member>& Reflect::member_list(void* obj) {
    return member_list_[obj];
}

} // namespace reflect