#include <reflect/reflect.h>

namespace reflect {

Reflect* Reflect::reflect_ = NULL;

Reflect::Reflect() {

}
Reflect::~Reflect() {

}

Reflect* Reflect::GetInstance() {
    if (reflect_ == NULL) {
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

}