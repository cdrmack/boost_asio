// synchronous TCP server

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

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

            // TODO
        }

        ctx.run();
    }

    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
