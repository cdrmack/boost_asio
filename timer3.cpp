#include <boost/asio.hpp>
#include <functional>
#include <iostream>

void print(const boost::system::error_code & /*error*/,
           boost::asio::steady_timer *timer, int *count)
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);

        timer->expires_at(
            timer->expiry() +
            boost::asio::chrono::seconds(1)); // run timer again after 1 second

        timer->async_wait(
            std::bind(print, boost::asio::placeholders::error, timer, count));
    }
}

int main()
{
    boost::asio::io_context io;
    int count = 0;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(1));

    timer.async_wait(
        std::bind(print, boost::asio::placeholders::error, &timer, &count));

    io.run();

    std::cout << "final count is: " << count << std::endl;

    return 0;
}
