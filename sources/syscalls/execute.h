#ifndef MYSHELL_EXECUTE_H
#define MYSHELL_EXECUTE_H


#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

#include "systemcallerror.h"
#include "systemcalls.h"
#include "../arguments/Arguments.h"

namespace syscalls {
    int execute(const std::vector<arguments::Arguments> &arguments_vector, const std::vector<std::string> &envp);

    int execute(const arguments::Arguments &arguments, const std::vector<std::string> &envp,
                int from_fd, int to_fd);
}

#endif //MYSHELL_EXECUTE_H
