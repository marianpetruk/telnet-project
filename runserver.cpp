#include "boost/asio.hpp"

#include "server/Server.h"


int main() {
    boost::asio::io_service io_service;
    Server server(io_service, 2014);
    io_service.run();
}
