#ifndef ECHOSERVER_SERVER_H
#define ECHOSERVER_SERVER_H


#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "Session.h"
#include "database/UserMap.h"

namespace server {
    class Server {
    public:
        boost::asio::ip::tcp::acceptor tcp_acceptor;
        database::UsersMap user_map;

        Server(boost::asio::io_service &io_service, unsigned short port);

    private:
        void start_accept();

        void handle_accept(std::shared_ptr<Session> new_session,
                           const boost::system::error_code &error);
    };
}

#endif //ECHOSERVER_SERVER_H
