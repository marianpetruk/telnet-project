#ifndef ECHOSERVER_SERVER_H
#define ECHOSERVER_SERVER_H


#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Session.h"
#include "shell/interpreter/Interpreter.h"
#include "shell/mybuiltins/Merrno.h"
#include "shell/mybuiltins/Mcd.h"
#include "shell/mybuiltins/Mpwd.h"
#include "shell/mybuiltins/Mexit.h"
#include "shell/mybuiltins/FileInterpreter.h"
#include "shell/mybuiltins/Mecho.h"
#include "shell/mybuiltins/Mexport.h"


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
