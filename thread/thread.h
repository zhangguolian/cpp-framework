#pragma once

#include <list>
#include <map>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>

namespace thread {

class Thread {
public:
    typedef boost::function<void(void)> Function;

    Thread();
    ~Thread();

    void Start();
    void Stop();
    void Join();

    void PostTask(Function func);
    //void PostDelayTask(Function func);
    
    int CreateTimerTask(Function func, int delay_seconds);
    void CancelTimerTask(int timer_id);

private:
    void TimerThread();
    void TaskThread();
    void TimerCallBack(const boost::system::error_code& err, 
                       boost::asio::deadline_timer* timer,
                       int timer_id,
                       int delay_seconds,
                       Function func);

private:
    int timer_id_;
    bool is_running_;
    boost::mutex timer_mutex_;
    boost::mutex task_mutex_;
    boost::thread timer_thread_;
    boost::thread task_thread_;
    boost::asio::io_service io_service_;
    std::list<Function> task_list_;
    std::map<int, std::unique_ptr<boost::asio::deadline_timer>> timer_list_;
};

};