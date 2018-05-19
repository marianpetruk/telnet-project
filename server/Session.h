#ifndef ECHOSERVER_SESSION_H
#define ECHOSERVER_SESSION_H


#include "boost/asio.hpp"
#include <iostream>
#include <sstream>

#include "shell/SessionAdapter.h"
#include "shell/interpreter/Interpreter.h"


class Session : public std::enable_shared_from_this<Session> {
public:
    Session(boost::asio::io_service &io_service, myshell::Interpreter &interpreter);

    ~Session();

    void start();

    boost::asio::ip::tcp::socket& get_socket();

private:
    int bash_fd;

    static std::string delim;

    boost::asio::ip::tcp::socket tcp_socket;
    boost::asio::streambuf data;

    myshell::Interpreter interpreter;
    SessionAdapter session_adapter;

    void read_login();

    void process_login(std::size_t  length);

    void read_socket();

    void write_socket(std::size_t  length);
};

#endif //ECHOSERVER_SESSION_H
