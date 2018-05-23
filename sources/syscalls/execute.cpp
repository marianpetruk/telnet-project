#include "execute.h"


int execute_many(const std::vector<arguments::Arguments> &arguments_vector, const std::vector<std::string> &envp) {
    int pipefd[arguments_vector.size() - 1][2];
    for (int i = 0; i < arguments_vector.size() - 1; ++i) {
        if (pipe(pipefd[i]) == -1) {
            int errno_copy = errno;
            for (int j = 0; j < i; ++j) {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }
            throw syscalls::SystemCallError(errno_copy);
        }
    }

//    for (int i = 0; i < arguments_vector.size() - 1; ++i) {
//        std::cout << pipefd[i][0] << ", " << pipefd[i][1] << std::endl;
//    }

    for (int i = 0; i < arguments_vector.size(); ++i) {
        if (i == 0) {
            syscalls::execute(arguments_vector[i], envp, -1, pipefd[i][1]);
            close(pipefd[i][1]);
        } else if (i == arguments_vector.size() - 1) {
            syscalls::execute(arguments_vector[i], envp, pipefd[i - 1][0], -1);
            close(pipefd[i - 1][0]);
        } else {
            syscalls::execute(arguments_vector[i], envp, pipefd[i - 1][0], pipefd[i][1]);
            close(pipefd[i - 1][0]);
            close(pipefd[i][1]);
        }
    }
    return 0;
}

int execute_single(const std::vector<arguments::Arguments> &arguments_vector, const std::vector<std::string> &envp) {
    return syscalls::execute(arguments_vector[0], envp, -1, -1);
}


int syscalls::execute(const std::vector<arguments::Arguments> &arguments_vector, const std::vector<std::string> &envp) {
    switch (arguments_vector.size()) {
        case 0:
            return 0;
        case 1:
            return execute_single(arguments_vector, envp);
        default:
            return execute_many(arguments_vector, envp);
    }
}


int syscalls::execute(const arguments::Arguments &arguments, const std::vector<std::string> &envp,
                      int from_fd, int to_fd) {
    pid_t pid = fork();
    if (pid == -1) {
        throw SystemCallError(errno);
    } else if (pid > 0) {
        // parent process
        if (!arguments.is_fone()) {
            int status;
            waitpid(pid, &status, 0);
            if (status) {
                throw SystemCallError(status);
            }
        }
        return 0;
    } else {
        // child process
        if (arguments.is_fone()) {
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);
        }

        if (from_fd != -1) {
            try {
                change_descriptor(STDIN_FILENO, from_fd);
            }
            catch (syscalls::SystemCallError &e) {
            }
        }
        if (to_fd != -1) {
            try {
                change_descriptor(STDOUT_FILENO, to_fd);
            }
            catch (syscalls::SystemCallError &e) {
            }
        }
        for (auto &redirect : arguments.get_redirects()) {
            try {
                redirect.apply();
            }
            catch (syscalls::SystemCallError &e) {
            }
        }

        std::vector<const char *> child_args;
        for (const auto &i : arguments.get_argv()) {
            child_args.push_back(i.c_str());
        }
        child_args.push_back(nullptr);
        std::vector<const char *> child_envp;
        for (const auto &i : envp) {
            child_envp.push_back(i.c_str());
        }
        child_envp.push_back(nullptr);
        execvpe(arguments.get_argv()[0].c_str(), const_cast<char *const *>(child_args.data()),
                const_cast<char *const *>(child_envp.data()));
        exit(EXIT_FAILURE);
    }
}
