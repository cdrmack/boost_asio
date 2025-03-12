// synchronous TCP server

#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

std::string make_daytime()
{
    std::time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_context ctx;

        tcp::acceptor acceptor(ctx, tcp::endpoint(tcp::v4(), 13));

        while (true)
        {
            tcp::socket socket(ctx);
            acceptor.accept(socket);

            std::cout << "[server] accepted" << std::endl;

            std::string msg = make_daytime();

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
        }

        ctx.run();
    }

    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
