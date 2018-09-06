#include <iostream>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& err, boost::asio::deadline_timer* pt)
{
    std::cout<<"hello,world!\n";
    pt->expires_at(pt->expires_at() + boost::posix_time::seconds(2)) ;
    pt->async_wait(boost::bind(print, _1, pt));
}

typedef boost::function<int(void)> Func;

int main() {
    boost::asio::io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(2));
    t.async_wait(boost::bind(print, _1, &t));
    io.run();
    
    return 0;
}