#include "Session.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


std::string Session::delim = "</bbp>";

Session::Session(asio::io_service &io_service, myshell::Interpreter &interpreter):
        tcp_socket(io_service), interpreter(interpreter) {};

Session::~Session() {
    std::cout << "Closed session with socket: " << tcp_socket.native_handle() << std::endl;
}

void Session::start() {
    std::cout << "Started session with socket: " << tcp_socket.native_handle() << std::endl;
    read_socket();
}

ip::tcp::socket& Session::get_socket() { return tcp_socket; }

void Session::read_socket() {
    auto self(shared_from_this());  // using self to prevent delete in lambda function
    asio::async_read_until(
            tcp_socket, data, Session::delim,
            [this, self](boost::system::error_code ec, std::size_t length){
                if (!ec) {
                    write_socket(length);
                }
            });
}

void Session::write_socket(std::size_t  length) {
    auto self(shared_from_this());  // using self to prevent delete in lambda function

    std::string command(asio::buffers_begin(data.data()),
                        asio::buffers_begin(data.data()) + length - Session::delim.size());
    data.consume(length);

    std::cout << "From " << tcp_socket.native_handle() << " executing: " << command << std::endl;
    interpreter.interpret(command, variables_map);

    asio::async_write(
            tcp_socket, asio::buffer(Session::delim),
            [this, self](boost::system::error_code ec, std::size_t /* length */){
                if (!ec) {
                    read_socket();
                }
            });
}
