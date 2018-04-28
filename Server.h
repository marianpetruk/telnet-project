#ifndef ECHOSERVER_SERVER_H
#define ECHOSERVER_SERVER_H


#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Session.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


class Server {
public:
    Server(asio::io_service &io_service, int port);

private:
    static std::string delim;

    ip::tcp::acceptor tcp_acceptor;

    void start_accept();

    void handle_accept(std::shared_ptr<Session> new_session,
                       const boost::system::error_code& error);
};

#endif //ECHOSERVER_SERVER_H
