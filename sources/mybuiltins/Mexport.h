#ifndef MYSHELL_MEXPORT_H
#define MYSHELL_MEXPORT_H


#include "../Executor.h"
#include "../interpreter/Interpreter.h"

namespace myshell {
    class Mexport : public Executor {
    protected:
        Interpreter &interpreter;

        void show_help() override;

        int execute_command(const std::vector<std::string> &argv) override;

    public:
        Mexport(Interpreter &interpreter);
    };
}


#endif //MYSHELL_MEXPORT_H
