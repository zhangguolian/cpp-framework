#include <async/async.h>

void print(int a, int b) {
    std::cout<< "print:" << a+b << std::endl;
}

void print1(int a, int b) {
    std::cout<< "print1:" << a+b << std::endl;
}

void print_once(int a, int b) {
    std::cout<< "print_once:" << a+b << std::endl;
}

int main() {
    std::shared_ptr<async::Thread> main_thread;
    main_thread.reset(new async::Thread(1));
    async::Timer timer; 
    async::Timer timer1; 

    timer.CreateTimerTask(boost::bind(print, 1, 2), 2, main_thread);
    timer.CreateOnceTimerTask(boost::bind(print_once, 1, 2), 2, main_thread);
    timer1.CreateTimerTask(boost::bind(print1, 1, 2), 2, main_thread);

    main_thread->Join();
    
    return 0;
}