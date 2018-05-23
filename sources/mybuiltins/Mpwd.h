#ifndef MYSHELL_MPWD_H
#define MYSHELL_MPWD_H


#include "../Executor.h"
#include "../syscalls/systemcalls.h"

namespace myshell {
    class Mpwd : public Executor {
    protected:
        void show_help() override;

        int execute_command(const std::vector<std::string> &argv) override;
    };
}

#endif //MYSHELL_MPWD_H
