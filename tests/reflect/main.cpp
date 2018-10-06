#include <reflect/reflect.hpp>
#include <iostream>
#include <string>

struct Test {
    int a;
    std::string b;
    float c;
};

REFLECT_REGIST(Test, int, a);
REFLECT_REGIST(Test, std::string, b);
REFLECT_REGIST(Test, float, c);

template<class T>
void ReflectMember(const T& data) {
    auto members = REFLECH_MEMBERS(T);
    for (size_t i = 0; i < members.size(); i++) {
        if (reflect::TypeIsString(members[i].type)) {
            printf("this is string type, ");
        }
        printf("%s %s\n", members[i].type.c_str(), members[i].name.c_str());
    }
}

int main() {
    Test test;
    test.a = 1;
    test.b = "test";
    test.c = 0.1;
    ReflectMember(test);

    return 0;
}