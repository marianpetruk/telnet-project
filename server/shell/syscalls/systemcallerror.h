#ifndef MYSHELL_SYSTEMCALLERROR_H
#define MYSHELL_SYSTEMCALLERROR_H


#include <string.h>
#include <exception>
#include <errno.h>

namespace syscalls {
    class SystemCallError : public std::exception {
    private:
        int errorcode;
    public:
        explicit SystemCallError(int error);

        const char *what() const throw();
    };
}

#endif //MYSHELL_SYSTEMCALLERROR_H
