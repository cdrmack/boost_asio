#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <system_error>

const boost::asio::ip::udp::endpoint
    SERVER_ENDPOINT(boost::asio::ip::address::from_string("127.0.0.1"), 8000);

void server()
{
    using namespace boost::asio;

    io_context ctx;

    ip::udp::socket server_socket(ctx, SERVER_ENDPOINT);

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
    using namespace boost::asio;

    io_context ctx;

    const ip::udp::endpoint client_endpoint(ip::udp::v4(), 0);
    ip::udp::socket client_socket(ctx, client_endpoint);

    std::string msg = "hello from the client!";

    client_socket.async_send_to(
        buffer(msg.data(), msg.length()), SERVER_ENDPOINT,
        [](std::error_code ec, std::size_t bytes)
        {
            if (ec || bytes == 0)
            {
                std::cout << "[client] error while sending data" << std::endl;
                return;
            }

            std::cout << "[client] sent " << bytes << "bytes" << std::endl;
        });

    ctx.run();
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
