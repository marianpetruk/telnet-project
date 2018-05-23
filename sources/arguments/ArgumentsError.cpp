#include "ArgumentsError.h"


namespace arguments {
    ArgumentsError::ArgumentsError(const std::string &text) : text(text) {}

    const char *ArgumentsError::what() const throw() {
        return text.c_str();
    }
}
