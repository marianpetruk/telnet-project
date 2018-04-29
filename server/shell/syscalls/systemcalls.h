#ifndef MYSHELL_SYSTEMCALLS_H
#define MYSHELL_SYSTEMCALLS_H


#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "systemcallerror.h"

namespace syscalls {
    int execute(const std::vector<std::string> &argv,
                const std::map<std::string, std::string> &envp, int out_descriptor);

    std::string real_path(std::string &path);

    struct stat get_stat(const std::string &filename);

    bool is_directory(const std::string &filename);

    std::string get_working_directory();

    int change_directory(std::string destination);
}

#endif //MYSHELL_SYSTEMCALLS_H
