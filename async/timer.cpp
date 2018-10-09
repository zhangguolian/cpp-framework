#include <async/timer.h>

#include <async/thread.h>

namespace async {

TimerDevice Timer::timer_device_;

TimerDevice::TimerDevice() {
    thread_ = boost::thread(boost::bind(
                &TimerDevice::TimerThread, this));
}
TimerDevice::~TimerDevice() {

}

void TimerDevice::TimerThread() {
    boost::asio::io_service::work work(io_service_);
    io_service_.run();
    
    return;
}

Timer::Timer()
      : timer_id_(1) {

}
Timer::~Timer() {

}

int Timer::CreateTimerTask(boost::function<void(void)> task, 
                           const boost::posix_time::time_duration& expiry_time,
                           std::shared_ptr<Thread> task_thread) {
    mutex_.lock();
    int timer_id = timer_id_++;
    mutex_.unlock();

    std::shared_ptr<boost::asio::deadline_timer> timer;
    timer.reset(new boost::asio::deadline_timer(timer_device_.io_service_, expiry_time));
    timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
        timer_id, expiry_time, task, task_thread));

    mutex_.lock();
    timer_list_[timer_id] = timer;
    mutex_.unlock();

    return timer_id; 
}
void Timer::CancelTimerTask(int timer_id) {
    mutex_.lock();
    timer_list_.erase(timer_id);
    mutex_.unlock();

    return;
}
void Timer::CreateOnceTimerTask(boost::function<void(void)> task,
                                const boost::posix_time::time_duration& expiry_time,
                                std::shared_ptr<Thread> task_thread) {
    std::shared_ptr<boost::asio::deadline_timer> timer;
    timer.reset(new boost::asio::deadline_timer(timer_device_.io_service_, expiry_time));
    timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
        0, expiry_time, task, task_thread));
}

void Timer::TimerCallBack(const boost::system::error_code& err, 
                          std::shared_ptr<boost::asio::deadline_timer> timer,
                          int timer_id,
                          boost::posix_time::time_duration expiry_time,
                          boost::function<void(void)> task,
                          std::shared_ptr<Thread> task_thread) {
    mutex_.lock();
    if (timer_id != 0 && timer_list_.find(timer_id) == timer_list_.end()) {
        mutex_.unlock();
        return;
    }
    mutex_.unlock();

    task_thread->PostTask(task);

    if (timer_id != 0) {
        timer->expires_at(timer->expires_at() + expiry_time) ;
        timer->async_wait(boost::bind(&Timer::TimerCallBack, this, _1, timer, 
            timer_id, expiry_time, task, task_thread));
    }

    return;
}

}