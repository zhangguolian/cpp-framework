#include <thread/thread.h>

namespace thread {
Thread::Thread()
       : timer_id_(0)
       , is_running_(false) {

}
Thread::~Thread() {
    Stop();
}

void Thread::Start() {
    if (is_running_) {
        return;
    }

    is_running_ = true;
    timer_thread_ = boost::thread(boost::bind(
        &Thread::TimerThread, this));
    task_thread_ = boost::thread(boost::bind(
        &Thread::TaskThread, this));

    return;
}
void Thread::Stop() {
    is_running_ = false;
    timer_thread_.join();
    task_thread_.join();

    timer_list_.clear();
    task_list_.clear();

    return;
}
void Thread::Join() {
    timer_thread_.join();
    task_thread_.join();

    return;
}

void Thread::PostTask(Function func) {
    task_mutex_.lock();
    task_list_.push_back(func);
    task_mutex_.unlock();

    return;
}

int Thread::CreateTimerTask(Function func, int delay_seconds) {
    timer_mutex_.lock();
    int timer_id = timer_id_++;
    timer_mutex_.unlock();

    boost::asio::deadline_timer* timer = new boost::asio::deadline_timer(
        io_service_, boost::posix_time::seconds(delay_seconds));
    timer->async_wait(boost::bind(&Thread::TimerCallBack, this, _1, timer, timer_id, delay_seconds, func));

    timer_mutex_.lock();
    timer_list_[timer_id].reset(timer);
    timer_mutex_.unlock();

    return timer_id; 
}
void Thread::CancelTimerTask(int timer_id) {
    timer_mutex_.lock();
    timer_list_.erase(timer_id);
    timer_mutex_.unlock();

    return;
}

void Thread::TimerThread() {
    while (is_running_) {
        io_service_.run();
    }

    return;
}
void Thread::TaskThread() {
    while (is_running_) {
        task_mutex_.lock();
        if (task_list_.empty()) {
            task_mutex_.unlock();
            continue;
        }

        Function func = task_list_.front();
        task_list_.pop_front();
        task_mutex_.unlock();

        func();
    }

    return;
}
void Thread::TimerCallBack(const boost::system::error_code& err, 
                           boost::asio::deadline_timer* timer,
                           int timer_id,
                           int delay_seconds,
                           Function func) {
    timer_mutex_.lock();
    if (timer_list_.find(timer_id) == timer_list_.end()) {
        timer_mutex_.unlock();
        return;
    }
    timer_mutex_.unlock();

    PostTask(func);

    if (delay_seconds > 0) {
        timer->expires_at(timer->expires_at() + boost::posix_time::seconds(delay_seconds)) ;
        timer->async_wait(boost::bind(&Thread::TimerCallBack, this, _1, timer, timer_id, delay_seconds, func));
    }

    return;
}
}
