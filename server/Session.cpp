#include "Session.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


namespace server {
    const size_t Session::size;
    std::string Session::delim = "</bbp>";

    Session::Session(asio::io_service &io_service) : tcp_socket(io_service) {}

    Session::~Session() {
        kill(bash_id, SIGKILL);
        close(bash_fd);
        std::cout << "Closed session with socket: " << tcp_socket.native_handle() << std::endl;
    }

    void Session::start() {
        std::cout << "Started session with socket: " << tcp_socket.native_handle() << std::endl;
        read_login();
    }

    ip::tcp::socket &Session::get_socket() { return tcp_socket; }

    void Session::read_login() {
        auto self(shared_from_this());  // using self to prevent delete in lambda function
        asio::async_read_until(
                tcp_socket, streambf, Session::delim,
                [this, self](boost::system::error_code ec, std::size_t length) {
                    if (!ec) {
                        process_login(length);
                    }
                });
    }

    void Session::process_login(std::size_t length) {
        std::string username(asio::buffers_begin(streambf.data()),
                             asio::buffers_begin(streambf.data()) + length - Session::delim.size());
        streambf.consume(length);

        if (start_shell("./myshell", tcp_socket.native_handle(), bash_fd, bash_id)) {
            start_reading();
        }
    }

    void Session::start_reading() {
        auto self(shared_from_this());
        tcp_socket.async_read_some(boost::asio::buffer(data, Session::size),
                                   [self, this] (boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                read_handler(length);
            }
        });
    }

    void Session::read_handler(size_t length) {
        std::string response(data, data + length);
        write(bash_fd, response.data(), response.size());
        start_reading();
    }
}
