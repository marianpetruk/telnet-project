#ifndef ECHOSERVER_SESSION_H
#define ECHOSERVER_SESSION_H


#include "boost/asio.hpp"
#include <iostream>
#include <sstream>

#include <unistd.h>
#include <sys/wait.h>

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::io_service &io_service);

    ~Session();

    void start();

    boost::asio::ip::tcp::socket& get_socket();

private:
    static std::string delim;

    boost::asio::ip::tcp::socket tcp_socket;
    boost::asio::streambuf data;
    void read_login();

    void process_login(std::size_t  length);
};

#endif //ECHOSERVER_SESSION_H
