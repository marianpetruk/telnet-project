#include "Merrno.h"


namespace myshell {
    Merrno::Merrno(Interpreter &interpreter) : interpreter(interpreter) {};

    void Merrno::show_help() {
        std::cout << "Usage: merrno [-h|--help]" << std::endl;
    }

    int Merrno::execute_command(const std::vector<std::string> &argv) {
        if (argv.size() != 1) {
            std::cerr << "Too many arguments" << std::endl;
            return INVARG;
        }
        std::cerr << "Error code: " << interpreter.MYERRNO << ". ";
        switch (interpreter.MYERRNO) {
            case EXECFD:
                std::cerr << "Execution failed." << std::endl;
                break;
            case EXECCP:
                std::cerr << "Execution completed." << std::endl;
                break;
            case INVARG:
                std::cerr << "Invalid arguments." << std::endl;
                break;
            default:
                std::cerr << "Some strange error." << std::endl;
        }
        return EXECCP;
    }
}
