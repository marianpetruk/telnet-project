#ifndef MYSHELL_SYSTEMCALLS_H
#define MYSHELL_SYSTEMCALLS_H


#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#include "systemcallerror.h"

namespace syscalls {
    std::string get_working_directory();

    std::string get_hostname();

    int change_directory(const std::string &destination);

    int open_file(const std::string &filename);

    int change_descriptor(int from, int to);
}

#endif //MYSHELL_SYSTEMCALLS_H
