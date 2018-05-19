#include "Session.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


std::string Session::delim = "</bbp>";

Session::Session(asio::io_service &io_service, myshell::Interpreter &interpreter):
        tcp_socket(io_service), interpreter(interpreter), session_adapter(){}

Session::~Session() {
    std::cout << "Closed session with socket: " << tcp_socket.native_handle() << std::endl;
}

void Session::start() {
    session_adapter.set_out_descriptor(tcp_socket.native_handle());
    std::cout << "Started session with socket: " << tcp_socket.native_handle() << std::endl;
    read_login();
}

ip::tcp::socket& Session::get_socket() { return tcp_socket; }

void Session::read_login() {
    auto self(shared_from_this());  // using self to prevent delete in lambda function
    asio::async_read_until(
            tcp_socket, data, Session::delim,
            [this, self](boost::system::error_code ec, std::size_t length){
                if (!ec) {
                    process_login(length);
                }
            });
}

void Session::process_login(std::size_t length) {
    auto self(shared_from_this());  // using self to prevent delete in lambda function

    std::string username(asio::buffers_begin(data.data()),
                        asio::buffers_begin(data.data()) + length - Session::delim.size());
    data.consume(length);

    int pipe_fd[2];
    pipe(pipe_fd);
    int pid = fork();
    if (pid < 0) {
        tcp_socket.close();
    }
    else if (pid == 0) {
//        dup2(tcp_socket.native_handle(), STDIN_FILENO);
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(tcp_socket.native_handle(), STDOUT_FILENO);
        dup2(tcp_socket.native_handle(), STDERR_FILENO);
        std::cout << "bash" << std::endl;
        execvp("bash", {NULL});
        std::cout << "failed" << std::endl;
    }
    else {
        bash_fd = pipe_fd[1];
        try {
            char data[1024];
            size_t length = tcp_socket.read_some(boost::asio::buffer(data));
            while (length != 0) {
                std::string response(data, data + length);
                response += "\n";
                write(bash_fd, response.data(), response.size());
                length = tcp_socket.read_some(boost::asio::buffer(data));
            }
        }
        catch (std::exception &e) {
            close(bash_fd);
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

//    session_adapter.get_variables_map().set("USERNAME", username);
//    std::string hostname = session_adapter.get_variables_map().get("HOSTNAME");
//    asio::write(tcp_socket, asio::buffer("[\033[1;32m" + username + "@" + hostname + "\033[0m " + "\033[1;34m" + session_adapter.get_variables_map().get("PWD") + "\033[0m]$ "));
//
//    asio::async_write(
//            tcp_socket, asio::buffer(Session::delim),
//            [this, self](boost::system::error_code ec, std::size_t /* length */){
//                if (!ec) {
//                    read_socket();
//                }
//            });
//}

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
    //write(bash_fd, command.data(), command.size());

    asio::async_write(
            tcp_socket, asio::buffer(Session::delim),
            [this, self](boost::system::error_code ec, std::size_t /* length */){
                if (!ec) {
                    read_socket();
                }
            });
}
