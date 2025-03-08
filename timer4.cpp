#include <boost/asio.hpp>
#include <functional>
#include <iostream>

class printer
{
  public:
    printer(boost::asio::io_context &io)
        : count(0), timer(io, boost::asio::chrono::seconds(1))
    {
        timer.async_wait(std::bind(&printer::print, this));
    };

    void print()
    {
        if (count < 5)
        {
            std::cout << count << std::endl;
            ++count;

            timer.expires_at(timer.expiry() + boost::asio::chrono::seconds(1));

            timer.async_wait(std::bind(&printer::print, this));
        }
    }

    ~printer() { std::cout << "final count is: " << count << std::endl; }

  private:
    int count;
    boost::asio::steady_timer timer;
};

int main()
{
    boost::asio::io_context io;

    printer p(io);

    io.run();

    return 0;
}
