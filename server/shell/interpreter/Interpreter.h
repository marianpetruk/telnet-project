#ifndef MYSHELL_INTERPRETER_H
#define MYSHELL_INTERPRETER_H


#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "getargs.h"
#include "../Executor.h"
#include "../SessionAdapter.h"
#include "../syscalls/systemcalls.h"

namespace myshell {
    class Interpreter {
    protected:
        std::map<std::string, myshell::Executor *> builtins;

    public:
        int MYERRNO = 0;

        void set_builtins(std::map<std::string, myshell::Executor *> builtins);

        void interpret(const std::vector<std::string> &argv, SessionAdapter &session_adapter);
        void interpret(const std::string &line, SessionAdapter &session_adapter);
    };
}

#endif //MYSHELL_INTERPRETER_H
