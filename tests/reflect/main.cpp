#include <reflect/reflect.hpp>
#include <iostream>
#include <string>

struct Test {
    Test() {
        REFLECT_REGIST(Test, this, int, a, &a);
        REFLECT_REGIST(Test, this, std::string, b, &b);
        REFLECT_REGIST(Test, this, float, c, &c);
    }
    ~Test() {
        REFLECT_UNREGIST(Test, this);
    }

    int a;
    std::string b;
    float c;
};

template<class T>
void ReflectMember(const T& data) {
    auto members = REFLECT_MEMBERS(T, &data);
    for (size_t i = 0; i < members.size(); i++) {
        if (reflect::TypeIsInt(members[i].type)) {
            printf("%s %s %d\n", members[i].type.c_str(), members[i].name.c_str(), *(int*)members[i].value);
            *(int*)members[i].value = 2;
        } else if (reflect::TypeIsFloat(members[i].type)) {
            printf("%s %s %f\n", members[i].type.c_str(), members[i].name.c_str(), *(float*)members[i].value);
        } else if (reflect::TypeIsString(members[i].type)) {
            printf("%s %s %s\n", members[i].type.c_str(), members[i].name.c_str(), (*(std::string*)members[i].value).c_str());
        }
        
    }
}

int main() {
    Test test;
    test.a = 1;
    test.b = "test";
    test.c = 0.1;
    ReflectMember(test);
    printf("a:%d\n", test.a);

    return 0;
}