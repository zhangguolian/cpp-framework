#include <thread/thread.h>

void print(int a, int b)
{
    std::cout<< "print:" << a+b << std::endl;
}

int main() {
    thread::Thread main_thread;
    
    main_thread.Start();
    main_thread.CreateTimerTask(boost::bind(print, 1, 2), 2);

    main_thread.Join();
    
    return 0;
}