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
    Thread(int thread_num = 1);
    ~Thread();

    void Join();
    void PostTask(const boost::function<void(void)>& task);

    boost::asio::io_service& io_service();

private:
    void TaskThread();

private:
    std::vector<std::unique_ptr<boost::thread>> thread_list_;
    boost::asio::io_service io_service_;
};

};