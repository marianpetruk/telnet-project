#ifndef ECHOSERVER_SESSION_H
#define ECHOSERVER_SESSION_H


#include "boost/asio.hpp"
#include <iostream>
#include <sstream>

#include "sources/interpreter/Interpreter.h"
#include "sources/variable_map/VariablesMap.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


class Session : public std::enable_shared_from_this<Session> {
public:
    myshell::Interpreter interpreter;
    vm::VariablesMap variables_map;

    Session(asio::io_service &io_service, myshell::Interpreter &interpreter);

    ~Session();

    void start();

    ip::tcp::socket& get_socket();

private:
    static std::string delim;

    ip::tcp::socket tcp_socket;
    asio::streambuf data;

    void read_socket();

    void write_socket(std::size_t  length);
};

#endif //ECHOSERVER_SESSION_H
