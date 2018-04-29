#ifndef MYSHELL_MEXPORT_H
#define MYSHELL_MEXPORT_H


#include "../Executor.h"

namespace myshell {
    class Mexport : public Executor {
    protected:
        void show_help() override;
        int execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) override;
    };
}


#endif //MYSHELL_MEXPORT_H
