#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <system_error>

void server()
{
    using namespace boost::asio;

    io_context ctx;

    const ip::udp::endpoint server_endpoint(
        ip::address::from_string("127.0.0.1"), 8000);
    ip::udp::socket server_socket(ctx, server_endpoint);

    char data[256];
    server_socket.async_receive(
        buffer(data),
        [&data](std::error_code ec, std::size_t bytes)
        {
            if (ec || bytes == 0)
            {
                std::cout << "[server] error while receiving data" << std::endl;
                return;
            }

            std::cout << "[server] received " << bytes << "bytes, [" << data
                      << "]" << std::endl;
        });

    ctx.run();
}

void client()
{
    // TODO
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./asio [server/client]" << std::endl;
        return 1;
    }

    const std::string variant = argv[1];

    if (variant == "server")
    {
        server();
        return 0;
    }

    if (variant == "client")
    {
        client();
        return 0;
    }

    std::cout << "Usage: ./asio [server/client]" << std::endl;
    return 1;
}
