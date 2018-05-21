#ifndef MYSHELL_MYSHELL_H
#define MYSHELL_MYSHELL_H


#include "interpreter/Interpreter.h"
#include "mybuiltins/Merrno.h"
#include "mybuiltins/Mcd.h"
#include "mybuiltins/Mpwd.h"
#include "mybuiltins/Mexit.h"
#include "mybuiltins/FileInterpreter.h"
#include "mybuiltins/Mecho.h"
#include "mybuiltins/Mexport.h"


namespace myshell {
    class Myshell: public Executor {
    protected:
        void show_help() override;
        int execute_command(const std::vector<std::string> &argv) override;
    public:
        void run(int argc, char *argv[]);
    };
}

#endif //MYSHELL_MYSHELL_H
