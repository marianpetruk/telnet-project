#include "Session.h"


namespace asio = boost::asio;
namespace ip = boost::asio::ip;


std::string Session::delim = "</bbp>";

Session::Session(asio::io_service &io_service): tcp_socket(io_service){}

Session::~Session() {
    std::cout << "Closed session with socket: " << tcp_socket.native_handle() << std::endl;
}

void Session::start() {
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
        close(pipe_fd[1]);
        tcp_socket.close();

        std::vector<const char*> child_args;
        child_args.push_back("./myshell");
        child_args.push_back(nullptr);
        execvp("./myshell", const_cast<char* const*>(child_args.data()));
    }
    else {
        close(pipe_fd[0]);
        int bash_fd = pipe_fd[1];
        try {
            char data[1024];
            size_t size = tcp_socket.read_some(boost::asio::buffer(data));
            while (size != 0) {
                std::string response(data, data + size);
                write(bash_fd, response.data(), response.size());
                size = tcp_socket.read_some(boost::asio::buffer(data));
            }
        }
        catch (std::exception &e) {
            close(bash_fd);
            int status;
            waitpid(pid, &status, 0);
        }
    }
}
