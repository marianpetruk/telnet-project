#ifndef MYSHELL_FILEINTERPRETER_H
#define MYSHELL_FILEINTERPRETER_H


#include <fstream>

#include "../Executor.h"
#include "../interpreter/Interpreter.h"

namespace myshell {
    class FileInterpreter : public Executor {
    protected:
        Interpreter& interpreter;

        void show_help() override;
        int execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) override;

    public:
        explicit FileInterpreter(Interpreter &interpreter);
    };
};


#endif //MYSHELL_FILEINTERPRETER_H
