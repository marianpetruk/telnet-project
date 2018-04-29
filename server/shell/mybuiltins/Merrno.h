#ifndef MYSHELL_MERRNO_H
#define MYSHELL_MERRNO_H


#include "../Executor.h"
#include "../interpreter/Interpreter.h"

namespace myshell {
    class Merrno : public Executor {
        void show_help() override;
        int execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) override;
    };
}

#endif //MYSHELL_MERRNO_H
