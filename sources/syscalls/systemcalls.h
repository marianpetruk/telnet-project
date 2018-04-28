#ifndef MYSHELL_SYSTEMCALLS_H
#define MYSHELL_SYSTEMCALLS_H


#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include "systemcallerror.h"

namespace syscalls {
    int execute(const std::vector<std::string> &argv, const std::vector<std::string> &envp);

    std::string get_working_directory();

    int change_directory(std::string destination);
}

#endif //MYSHELL_SYSTEMCALLS_H
