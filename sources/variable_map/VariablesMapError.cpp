#include "VariablesMapError.h"


namespace vm {
    VariablesMapError::VariablesMapError(std::string key) : key(key) {}

    const char *VariablesMapError::what() const throw() {
        return ("Failed: " + key).c_str();
    }
}
