#include <iostream>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print1(int a, int b)
{
    std::cout<< "print1:" << a+b << std::endl;
}

int print2(int a, int b)
{  
    return a+b;
}

typedef boost::function<void(void)> Func1;
typedef boost::function<int(void)> Func2;
typedef boost::function<void(int)> Func3;

int main() {
    Func1 f1 = boost::bind(print1, 1, 1);
    f1();

    Func2 f2 = boost::bind(print2, 1, 2);
    std::cout << f2() << std::endl;

    Func3 f3 = boost::bind(print1, 1, _1);
    f3(6);

    return 0;
}