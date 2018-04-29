#ifndef MYSHELL_VARIABLESMAPERROR_H
#define MYSHELL_VARIABLESMAPERROR_H


#include <exception>
#include <string>

namespace vm {
    class VariablesMapError : std::exception {
    private:
        std::string key;

    public:
        VariablesMapError(std::string key);

        const char *what() const throw();
    };
}


#endif //MYSHELL_VARIABLESMAPERROR_H
