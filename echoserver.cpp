#include <string>
#include <iostream>

#include <boost/asio.hpp>


namespace asio = boost::asio;
namespace ip = boost::asio::ip;

asio::io_service ioservice;
ip::tcp::endpoint tcp_endpoint(ip::tcp::v4(), 2014);
ip::tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
ip::tcp::socket tcp_socket{ioservice};

asio::streambuf data;
std::string delim = "\r\n";

void read_socket();
void write_socket(std::size_t  length);


void write_socket(std::size_t  length) {
    char received_data[length];
    data.sgetn(received_data, length);
    std::cout.write(received_data, length);
    asio::async_write(tcp_socket, asio::buffer(received_data, length),
                      [](boost::system::error_code ec, std::size_t /* length */){
        if (!ec) {
            read_socket();
        }
    });
}

void read_socket() {
    asio::async_read_until(tcp_socket, data, delim,
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
            std::cout << "Accepted. Descriptor: " << tcp_socket.native_handle() << std::endl;
            read_socket();
        }
    });
    ioservice.run();
}