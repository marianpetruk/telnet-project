#ifndef MYSHELL_MEXIT_H
#define MYSHELL_MEXIT_H


#include "../Executor.h"

namespace myshell {
    class Mexit : public Executor {
    protected:
        void show_help() override;

        int execute_command(const std::vector<std::string> &argv) override;
    };
}

#endif //MYSHELL_MEXIT_H
