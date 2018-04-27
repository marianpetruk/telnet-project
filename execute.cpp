#include "execute.h"


int execute(std::vector<std::string> &argv, int fd) {
    pid_t pid = fork();
    if (pid == -1) {
        return 0;
    }
    else if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        return 0;
    }
    else {
        // child process
        close(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        std::vector<const char*> child_argv;
        for (auto &val : argv) child_argv.push_back(val.c_str());
        child_argv.push_back(NULL);
        execvp(child_argv[0], const_cast<char* const*>(child_argv.data()));
        exit(EXIT_FAILURE);
    }
}
