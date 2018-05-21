#ifndef MYSHELL_MERRNO_H
#define MYSHELL_MERRNO_H


#include "../Executor.h"
#include "../interpreter/Interpreter.h"

namespace myshell {
    class Merrno : public Executor {
    protected:
        Interpreter& interpreter;

        void show_help() override;
        int execute_command(const std::vector<std::string> &argv) override;

    public:
        explicit Merrno(Interpreter &interpreter);
    };
}

#endif //MYSHELL_MERRNO_H
