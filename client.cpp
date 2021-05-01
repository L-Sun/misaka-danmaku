#include <iostream>

#include <asio.hpp>

using asio::ip::udp;

int main(int argc, char const* argv[]) {
    try {
        asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::endpoint remote(asio::ip::make_address("127.0.0.1"), 1543);

        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::string message;
        while (std::getline(std::cin, message)) {
            socket.send_to(asio::buffer(message), remote);
        }
        std::cout << "wait messaage send..." << std::endl;
        io_context.run();
        std::cout << "exit..." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
