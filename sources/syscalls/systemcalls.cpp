#include "systemcalls.h"


std::string syscalls::get_working_directory() {
    char current_path[FILENAME_MAX];
    if (!getcwd(current_path, FILENAME_MAX)) {
        throw SystemCallError(errno);
    }
    return std::string(current_path);
}

std::string syscalls::get_hostname() {
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, HOST_NAME_MAX) == -1) {
        throw SystemCallError(errno);
    }
    return std::string(hostname);
}

int syscalls::change_directory(const std::string &destination) {
    if (chdir(destination.c_str())) {
        throw SystemCallError(errno);
    }
    return 0;
}

int syscalls::open_file(const std::string &filename) {
    int fd = open(filename.c_str(), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd == -1) {
        throw SystemCallError(errno);
    }
    return fd;
}

int syscalls::change_descriptor(int from, int to) {
    if (dup2(to, from)) {
        throw SystemCallError(errno);
    }
    return 0;
}
