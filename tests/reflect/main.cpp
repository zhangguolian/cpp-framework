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
#include <iostream>
#include <string>

struct Test {
    // Define reflect params
    REFLECT_DEFINE(int, a);
    REFLECT_DEFINE(std::string, b);
    REFLECT_DEFINE(float, c);
};

template<class T>
void ReflectMember(const T& data) {
    // Parse all members of the object
    auto members = REFLECT_MEMBERS(&data);
    for (size_t i = 0; i < members.size(); i++) {
        if (reflect::TypeIsInt(members[i].type)) {
            printf("%s %s %d\n", members[i].type.c_str(), members[i].name.c_str(), *(int*)members[i].value);
            // Modify the value of an object member
            *(int*)members[i].value = 2;
        } else if (reflect::TypeIsFloat(members[i].type)) {
            printf("%s %s %f\n", members[i].type.c_str(), members[i].name.c_str(), *(float*)members[i].value);
        } else if (reflect::TypeIsString(members[i].type)) {
            printf("%s %s %s\n", members[i].type.c_str(), members[i].name.c_str(), (*(std::string*)members[i].value).c_str());
        }
        
    }
}

REFLECT_ARRAY_DEFINE(ArrayTest, Test);

int main() {
    Test test;
    test.a = 1;
    test.b = "test";
    test.c = 0.1;

    ReflectMember(test);
    // Verify that the modification was successful
    printf("a:%d\n", test.a);

    ArrayTest test_array;
    test_array.push_back(test);
    printf("test_array a:%d\n", test_array[0].a);

    reflect::Array* array = static_cast<reflect::Array*>((void*)(&test_array));
    if (array == NULL) {
        printf("static_cast Array fail\n");
        return -1;
    }

    printf("array size %d\n", int(array->size()));

    return 0;
}