#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


std::string delim = "\r\n";


class Session : public std::enable_shared_from_this<Session> {
public:
    Session(asio::io_service &io_service): tcp_socket(io_service) {};

    void start() {
        std::cout << "Started session with socket: " << tcp_socket.native_handle() << std::endl;
        read_socket();
    }

    ip::tcp::socket& get_socket() { return tcp_socket; }

private:
    ip::tcp::socket tcp_socket;
    asio::streambuf data;

    void read_socket() {
        auto self(shared_from_this());  // using self to prevent delete in lambda function
        asio::async_read_until(
                tcp_socket, data, delim,
                [this, self](boost::system::error_code ec, std::size_t length){
                    if (!ec) {
                        write_socket(length);
                    }
                });
    }

    void write_socket(std::size_t  length) {
        auto self(shared_from_this());  // using self to prevent delete in lambda function
        char received_data[length];
        data.sgetn(received_data, length);
        std::cout.write(received_data, length);
        asio::async_write(
                tcp_socket, asio::buffer(received_data, length),
                [this, self](boost::system::error_code ec, std::size_t /* length */){
                    if (!ec) {
                        read_socket();
                    }
                });
    }
};

class Server {
public:
    Server(asio::io_service &io_service):
            tcp_acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), 2014)) {
        start_accept();
    }

private:
    ip::tcp::acceptor tcp_acceptor;

    void start_accept() {
        std::shared_ptr<Session> session(new Session(tcp_acceptor.get_io_service()));

        tcp_acceptor.async_accept(
                session->get_socket(),
                boost::bind(&Server::handle_accept, this, session, asio::placeholders::error)
        );
    }

    void handle_accept(std::shared_ptr<Session> new_session,
                       const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
            start_accept();
        }
    }
};


int main() {
    asio::io_service io_service;
    Server server(io_service);
    io_service.run();
}
