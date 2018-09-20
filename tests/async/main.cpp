#include <async/async.h>

void print(int a, int b) {
    std::cout<< "print:" << a+b << std::endl;
}

void print_once(int a, int b) {
    std::cout<< "print_once:" << a+b << std::endl;
}

int main() {
    std::shared_ptr<async::Thread> main_thread;
    main_thread.reset(new async::Thread());
    async::Timer timer; 
    main_thread->Start();
    timer.Start();

    timer.CreateTimerTask(boost::bind(print, 1, 2), 2, main_thread);
    timer.CreateOnceTimerTask(boost::bind(print_once, 1, 2), 2, main_thread);

    main_thread->Join();
    
    return 0;
}