#include "Server.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


Server::Server(asio::io_service &io_service, unsigned short port):
        tcp_acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    std::shared_ptr<Session> session(new Session(tcp_acceptor.get_io_service()));

    tcp_acceptor.async_accept(
            session->get_socket(),
            boost::bind(&Server::handle_accept, this, session, asio::placeholders::error)
    );
}

void Server::handle_accept(std::shared_ptr<Session> new_session,
                   const boost::system::error_code& error) {
    if (!error) {
        new_session->start();
        start_accept();
    }
}
