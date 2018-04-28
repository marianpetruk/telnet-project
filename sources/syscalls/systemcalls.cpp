#include "systemcalls.h"


int syscalls::execute(const std::vector<std::string> &argv, const std::vector<std::string> &envp, int out_descriptor) {
    pid_t pid = fork();
    if (pid == -1) {
        throw SystemCallError(errno);
    }
    else if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);
        if (status) {
            throw SystemCallError(status);
        }
        return 0;
    }
    else {
        // child process
        close(STDOUT_FILENO);
        dup2(out_descriptor, STDOUT_FILENO);

        std::vector<const char*> child_args;
        for (const auto &i : argv) {
            child_args.push_back(i.c_str());
        }
        child_args.push_back(nullptr);
        std::vector<const char*> child_envp;
        for (const auto &i : envp) {
            child_envp.push_back(i.c_str());
        }
        child_envp.push_back(nullptr);
        execvpe(argv[0].c_str(), const_cast<char* const*>(child_args.data()),
                const_cast<char* const*>(child_envp.data()));
        exit(EXIT_FAILURE);
    }
}

std::string syscalls::get_working_directory() {
    char current_path[FILENAME_MAX];
    if (!getcwd(current_path, FILENAME_MAX)) {
        throw SystemCallError(errno);
    }
    return std::string(current_path);
}

int syscalls::change_directory(std::string destination) {
    if (chdir(destination.c_str())) {
        throw SystemCallError(errno);
    }
    return 0;
}
