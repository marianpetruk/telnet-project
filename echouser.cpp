#include <boost/asio.hpp>
#include <array>
#include <string>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
streambuf data;
std::string delim = "\r\n";


void connect_handler(const boost::system::error_code &ec);

void read_handler(const boost::system::error_code &ec,
                  std::size_t bytes_transferred) {
    if (!ec)
    {
        char received_data[bytes_transferred];
        data.sgetn(received_data, bytes_transferred);
        std::cout.write(received_data, bytes_transferred);
        connect_handler(ec);
    }
}

void write_handler(const boost::system::error_code &ec,
                  std::size_t bytes_transferred) {
    async_read_until(tcp_socket, data, delim, read_handler);
}

void connect_handler(const boost::system::error_code &ec) {
    if (!ec)
    {
        std::string r;
        std::getline(std::cin, r);
        r += delim;
        async_write(tcp_socket, buffer(r), write_handler);
    }
}

void resolve_handler(const boost::system::error_code &ec,
                     tcp::resolver::iterator it) {
    if (!ec)
        tcp_socket.async_connect(*it, connect_handler);
}

int main() {
    tcp::resolver::query q{"localhost", "2014"};
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();
}