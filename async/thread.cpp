#include <async/thread.h>

namespace async {

Thread::Thread(int thread_num) {
    for (int i = 0; i < thread_num; i++) {
        boost::thread* task_thread = new boost::thread(boost::bind(
            &Thread::TaskThread, this));
        thread_list_.push_back(std::unique_ptr<boost::thread>());
        thread_list_[thread_list_.size()-1].reset(task_thread);
    } 
}
Thread::~Thread() {

}

void Thread::Join() {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        thread_list_[i]->join();
    }

    return;
}

void Thread::PostTask(const boost::function<void(void)>& task) {
    io_service_.post(task);

    return;
}

boost::asio::io_service& Thread::io_service() {
    return io_service_;
}

bool Thread::operator==(const boost::thread::id& id) const {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        if (thread_list_[i]->get_id() == id) {
            return true;
        }
    }

    return false;
}
bool Thread::operator!=(const boost::thread::id& id) const {
    for (size_t i = 0; i < thread_list_.size(); i++) {
        if (thread_list_[i]->get_id() == id) {
            return false;
        }
    }

    return true;
}

void Thread::TaskThread() {
    boost::asio::io_service::work work(io_service_);
    io_service_.run();
    
    return;
}

}
