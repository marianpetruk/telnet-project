#ifndef MYSHELL_ARGUMENTSERROR_H
#define MYSHELL_ARGUMENTSERROR_H


#include <string>

namespace arguments {
    class ArgumentsError : public std::exception {
    private:
        std::string text;

    public:
        ArgumentsError(const std::string &text);

        const char *what() const throw();
    };
}


#endif //MYSHELL_ARGUMENTSERROR_H
