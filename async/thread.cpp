#include <async/thread.h>

namespace async {

Thread::Thread()
       : is_running_(false) {

}
Thread::~Thread() {
    Stop();
}

void Thread::Start(int thread_num) {
    if (is_running_) {
        return;
    }

    is_running_ = true;
    for (int i = 0; i < thread_num; i++) {
        boost::thread* task_thread = new boost::thread(boost::bind(
            &Thread::TaskThread, this));
        thread_list_.push_back(std::unique_ptr<boost::thread>());
        thread_list_[thread_list_.size()-1].reset(task_thread);
    } 

    return;
}
void Thread::Stop() {
    if (!is_running_) {
        return;
    }

    is_running_ = false;
    
    for (size_t i = 0; i < thread_list_.size(); i++) {
        thread_list_[i]->join();
    }

    thread_list_.clear();

    return;
}
void Thread::Join() {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        thread_list_[i]->join();
    }

    return;
}

void Thread::PostTask(boost::function<void(void)> task) {
    io_service_.post(task);

    return;
}

void Thread::TaskThread() {
    boost::asio::io_service::work work(io_service_);
    io_service_.run();
    
    return;
}

}
