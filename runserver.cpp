#include "boost/asio.hpp"
#include <boost/lexical_cast.hpp>

#include "server/Server.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: shellserver <port>" << std::endl;
        return -1;
    }
    try {
        unsigned short port;
        port = boost::lexical_cast<unsigned short>(argv[1]);
        boost::asio::io_service io_service;
        server::Server server(io_service, port);
        io_service.run();
    }
    catch (boost::bad_lexical_cast &e) {
        std::cerr << "Invalid port" << std::endl;
        return -1;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
