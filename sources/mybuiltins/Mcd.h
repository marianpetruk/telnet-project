#ifndef MYSHELL_MCD_H
#define MYSHELL_MCD_H


#include "../Executor.h"
#include "../syscalls/systemcalls.h"

namespace myshell {
    class Mcd : public Executor {
    protected:
        void show_help() override;
        int execute_command(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) override;
    };
}

#endif //MYSHELL_MCD_H
