#include <boost/asio.hpp>
#include <iostream>

void print(const boost::system::error_code & /*error*/)
{
    std::cout << "Hello, world!" << std::endl;
}

int main()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(5));

    timer.async_wait(&print);

    io.run();

    std::cout << "nothing more to do" << std::endl;

    return 0;
}
