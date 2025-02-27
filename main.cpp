#include <iostream>
#include <string>

void server()
{
    // TODO
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
