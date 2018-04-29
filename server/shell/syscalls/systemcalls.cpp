#include "systemcalls.h"
#include <iostream>


int syscalls::execute(const std::vector<std::string> &argv,
                      const std::map<std::string, std::string> &envp, int out_descriptor) {
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
        // child process;
        setenv("PATH", envp.find("PATH")->second.c_str(), 1);
//        setenv("PWD", envp.find("PWD")->second.c_str(), 1);
        change_directory(envp.find("PWD")->second);
//        std::cout << get_working_directory() << std::endl;

        close(STDOUT_FILENO);
        dup2(out_descriptor, STDOUT_FILENO);

        std::vector<const char*> child_args;
        for (const auto &i : argv) {
            child_args.push_back(i.c_str());
        }
        child_args.push_back(nullptr);
        std::vector<const char*> child_envp;
        for (const auto &i : envp) {
            child_envp.emplace_back((i.first + "=" + i.second).c_str());
        }
        child_envp.push_back(nullptr);
        execvpe(argv[0].c_str(), const_cast<char* const*>(child_args.data()),
                const_cast<char* const*>(child_envp.data()));
        exit(EXIT_FAILURE);
    }
}

std::string syscalls::real_path(std::string &path) {
    char resolved_path[PATH_MAX];
    if (realpath(path.c_str(), resolved_path) == NULL) {
        throw SystemCallError(errno);
    }
    return std::string(resolved_path);
}

struct stat syscalls::get_stat(const std::string &filename){
    struct stat st;
    if (stat(filename.c_str(), &st)){
        throw SystemCallError(errno);
    }
    else{
        return st;
    }
}

bool syscalls::is_directory(const std::string &filename) {
    try {
        return S_ISDIR(get_stat(filename).st_mode);
    }
    catch (SystemCallError &e) {
        return false;
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
