#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));

    // blocking operation
    timer.wait();

    std::cout << "Hello, world!" << std::endl;

    return 0;
}
