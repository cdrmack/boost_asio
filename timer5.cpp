#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <thread>

class printer
{
  public:
    printer(boost::asio::io_context &io)
        : strand(boost::asio::make_strand(io)),
          timer1(io, boost::asio::chrono::seconds(1)),
          timer2(io, boost::asio::chrono::seconds(1)), count(0)
    {
        timer1.async_wait(boost::asio::bind_executor(
            strand, std::bind(&printer::print1, this)));
        timer2.async_wait(boost::asio::bind_executor(
            strand, std::bind(&printer::print2, this)));
    };

    void print1()
    {
        if (count < 5)
        {
            std::cout << "timer 1: " << count << std::endl;
            ++count;

            timer1.expires_at(timer1.expiry() +
                              boost::asio::chrono::seconds(1));
            timer1.async_wait(boost::asio::bind_executor(
                strand, std::bind(&printer::print1, this)));
        }
    }

    void print2()
    {
        if (count < 5)
        {
            std::cout << "timer 2: " << count << std::endl;

            timer2.expires_at(timer2.expiry() +
                              boost::asio::chrono::seconds(1));
            timer2.async_wait(boost::asio::bind_executor(
                strand, std::bind(&printer::print2, this)));
        }
    }

    ~printer() { std::cout << "final count is: " << count << std::endl; }

  private:
    // executor adapter, handlers dispatched through it are run one at a time
    boost::asio::strand<boost::asio::io_context::executor_type> strand;
    boost::asio::steady_timer timer1;
    boost::asio::steady_timer timer2;
    int count;
};

int main()
{
    boost::asio::io_context io;

    printer p(io);

    std::thread t([&] { io.run(); });

    io.run();
    t.join();

    return 0;
}
