#ifndef MYSHELL_INTERPRETER_H
#define MYSHELL_INTERPRETER_H


#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "getargs.h"
#include "../Executor.h"
#include "../arguments/Arguments.h"
#include "../variable_map/VariablesMap.h"
#include "../syscalls/execute.h"

namespace myshell {
    class Interpreter {
    protected:
        std::map<std::string, myshell::Executor *> builtins;

    public:
        int MYERRNO = 0;

        vm::VariablesMap &variablesMap;

        explicit Interpreter(vm::VariablesMap &vm);

        void set_builtins(std::map<std::string, myshell::Executor *> builtins);

        void interpret(const std::vector<arguments::Arguments> &arguments);

        void interpret(const std::string &line);
    };
}

#endif //MYSHELL_INTERPRETER_H
