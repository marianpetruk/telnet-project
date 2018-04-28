#include "Server.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


Server::Server(asio::io_service &io_service, unsigned short port):
        tcp_acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)) {
    const std::map<std::string, myshell::Executor*> builtins = {
            {"merrno",   new myshell::Merrno(interpreter)},
            {"mpwd",     new myshell::Mpwd()},
            {"mcd",      new myshell::Mcd()},
            {"mexit",    new myshell::Mexit()},
            {".",        new myshell::FileInterpreter(interpreter)},
            {"mecho",    new myshell::Mecho()},
            {"mexport",  new myshell::Mexport()}
    };
    interpreter.set_builtins(builtins);
    start_accept();
}

void Server::start_accept() {
    std::shared_ptr<Session> session(new Session(tcp_acceptor.get_io_service(), interpreter));

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


int main() {
    asio::io_service io_service;
    Server server(io_service, 2014);
    io_service.run();
}
