#include "start_shell.h"


namespace server {
    bool start_shell(const std::string &filename, const std::string& username,
                     int socket_fd, int& shell_fd, int& shell_id) {
        int pipe_fd[2];
        pipe(pipe_fd);
        int pid = fork();
        if (pid < 0) {
            return false;
        }
        else if (pid == 0) {
//        dup2(tcp_socket.native_handle(), STDIN_FILENO);
            dup2(pipe_fd[0], STDIN_FILENO);
            dup2(socket_fd, STDOUT_FILENO);
            dup2(socket_fd, STDERR_FILENO);
            close(pipe_fd[1]);
            setenv("USER", username.c_str(), 1);

            std::vector<const char *> child_args;
            child_args.push_back(filename.c_str());
            child_args.push_back(nullptr);
            execvp(filename.c_str(), const_cast<char *const *>(child_args.data()));
            exit(EXIT_FAILURE);
        } else {
            close(pipe_fd[0]);
            shell_fd = pipe_fd[1];
            shell_id = pid;
            return true;
        }
    }
}
