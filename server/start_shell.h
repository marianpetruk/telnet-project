#ifndef ECHOSERVER_START_SHELL_H
#define ECHOSERVER_START_SHELL_H


#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

namespace server {
    bool start_shell(const std::string& filename, int socket_fd, int& shell_fd, int& shell_id);
}

#endif //ECHOSERVER_START_SHELL_H
