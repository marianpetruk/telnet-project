#ifndef MYSHELL_MYBUILTIN_H
#define MYSHELL_MYBUILTIN_H


#include <vector>
#include <iostream>

#include "SessionAdapter.h"

#define   EXECFD    -1
#define   EXECCP     0
#define   INVARG     1


namespace myshell {
    class Executor {
    protected:
        virtual void show_help() = 0;
        virtual int execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) = 0;

    public:
        int execute(const std::vector<std::string> &argv, SessionAdapter &session_adapter);
    };
}

#endif //MYSHELL_MYBUILTIN_H
