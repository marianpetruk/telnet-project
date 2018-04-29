#include "systemcallerror.h"


syscalls::SystemCallError::SystemCallError(int error) {
    errorcode = error;
}

const char* syscalls::SystemCallError::what() const throw () {
    return strerror(errorcode);
}
