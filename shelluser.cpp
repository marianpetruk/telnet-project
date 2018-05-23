#include <boost/asio.hpp>
#include <array>
#include <string>
#include <iostream>

#include <thread>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
std::string delim = "</bbp>";


void send_data() {
    std::string req;
    while (std::getline(std::cin, req)) {
        write(tcp_socket, buffer(req + "\n"));
    }
}

void login_handler(const boost::system::error_code &ec,
                   std::size_t bytes_transferred) {
    if (!ec) {
        std::thread writer(send_data);
        writer.detach();

        try {
            char data[1024];
            size_t length = tcp_socket.read_some(boost::asio::buffer(data));
            while (length != 0) {
                std::string response(data, data + length);
                std::cout << response;
                length = tcp_socket.read_some(boost::asio::buffer(data));
            }
        }
        catch (std::exception &e) {
            tcp_socket.close();
            std::cout << "Connection lost" << std::endl;
        }
    }
}

void login(const boost::system::error_code &ec) {
    if (!ec) {
        std::cout << "Enter username: ";
        std::string result;
        std::getline(std::cin, result);                    // username
        std::string password(getpass("Enter password: ")); // password
        result += "\n" + password + delim;
        async_write(tcp_socket, buffer(result), login_handler);
    }
}

void resolve_handler(const boost::system::error_code &ec,
                     tcp::resolver::iterator it) {
    if (!ec)
        tcp_socket.async_connect(*it, login);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: shelluser <host> <port>" << std::endl;
        return -1;
    }
    tcp::resolver::query q{argv[1], argv[2]};
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();

    return 0;
}
