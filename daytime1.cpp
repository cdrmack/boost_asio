// synchronous TCP client

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: client <host>" << std::endl;
        return 1;
    }

    try
    {
        boost::asio::io_context ctx;

        // resolver takes a host name and service name and turns them into a
        // list of endpoints
        tcp::resolver resolver(ctx);
        tcp::resolver::results_type endpoints =
            resolver.resolve(argv[1], "daytime");

        tcp::socket socket(ctx);
        // boost::asio::connect(socket, endpoints);

        // TODO

        ctx.run();
    }

    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
