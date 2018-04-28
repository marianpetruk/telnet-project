#ifndef ECHOSERVER_SERVER_H
#define ECHOSERVER_SERVER_H


#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Session.h"
#include "sources/interpreter/Interpreter.h"
#include "sources/mybuiltins/Merrno.h"
#include "sources/mybuiltins/Mcd.h"
#include "sources/mybuiltins/Mpwd.h"
#include "sources/mybuiltins/Mexit.h"
#include "sources/mybuiltins/FileInterpreter.h"
#include "sources/mybuiltins/Mecho.h"
#include "sources/mybuiltins/Mexport.h"


class Server {
public:
    boost::asio::ip::tcp::acceptor tcp_acceptor;

    Server(boost::asio::io_service &io_service, unsigned short port);

private:
    myshell::Interpreter interpreter;

    void start_accept();

    void handle_accept(std::shared_ptr<Session> new_session,
                       const boost::system::error_code& error);
};

#endif //ECHOSERVER_SERVER_H
