#ifndef MYSHELL_MECHO_H
#define MYSHELL_MECHO_H


#include "../Executor.h"

namespace myshell {
    class Mecho : public Executor {
    protected:
        void show_help() override;
        int execute_command(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) override;
    };
};

#endif //MYSHELL_MECHO_H
