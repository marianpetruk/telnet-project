#ifndef MYSHELL_MYBUILTIN_H
#define MYSHELL_MYBUILTIN_H


#include <vector>
#include <iostream>

#include "variable_map/VariablesMap.h"

#define   EXECFD    -1
#define   EXECCP     0
#define   INVARG     1


namespace myshell {
    class Executor {
    protected:
        virtual void show_help() = 0;
        virtual int execute_command(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) = 0;

    public:
        int execute(const std::vector<std::string> &argv, vm::VariablesMap &variables_map);
    };
}

#endif //MYSHELL_MYBUILTIN_H
