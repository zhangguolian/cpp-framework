#pragma once

#include <list>
#include <map>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>

namespace async {

class Thread {
public:
    Thread();
    ~Thread();

    void Start(int thread_num = 1);
    void Stop();
    void Join();

    void PostTask(boost::function<void(void)> task);
    //void PostDelayTask(Function task);

private:
    void TaskThread();

private:
    bool is_running_;
    std::vector<std::unique_ptr<boost::thread>> thread_list_;
    boost::asio::io_service io_service_;
};

};