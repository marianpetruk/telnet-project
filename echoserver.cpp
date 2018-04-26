#include <string>
#include <iostream>

#include <boost/asio.hpp>


namespace asio = boost::asio;
namespace ip = boost::asio::ip;

const size_t max_length = 1024;

asio::io_service ioservice;
ip::tcp::endpoint tcp_endpoint(ip::tcp::v4(), 2014);
ip::tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
ip::tcp::socket tcp_socket{ioservice};

char data[max_length];

void read_socket();
void write_socket(std::size_t  length);


void write_socket(std::size_t  length) {
    std::cout.write(data, length);
    asio::async_write(tcp_socket, asio::buffer(data, length),
                      [](boost::system::error_code ec, std::size_t /* length */){
        if (!ec) {
            read_socket();
        }
    });
}

void read_socket() {
    tcp_socket.async_read_some(asio::buffer(data),
                               [](boost::system::error_code ec, std::size_t length){
        if (!ec) {
            write_socket(length);
        }
    });
}


int main() {
    tcp_acceptor.listen();
    tcp_acceptor.async_accept(tcp_socket, [](const boost::system::error_code &ec) {
        if (!ec) {
            std::cout << tcp_socket.native_handle() << std::endl;
            read_socket();
        }
    });
    ioservice.run();
}