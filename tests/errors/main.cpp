#include <errors/errors.h>
#include <string>
#include <iostream>

int main() {
    INIT_ERRORS_SIGNAL();

    std::string* ptr = NULL;
    std::cout << ptr->c_str() << std::endl;

    return 0;
}