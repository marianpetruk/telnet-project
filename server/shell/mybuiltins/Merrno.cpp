#include "Merrno.h"


namespace myshell {
    Merrno::Merrno(Interpreter &interpreter): interpreter(interpreter) {};

    void Merrno::show_help() {
        std::cout << "Usage: merrno [-h|--help]" << std::endl;
    }

    int Merrno::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        if (argv.size() != 1) {
            session_adapter.write_error("Too many arguments\n");
            return INVARG;
        }
        session_adapter.write_error("Error code: %d. ", session_adapter.MYERRNO);
        switch (session_adapter.MYERRNO) {
            case EXECFD:
                session_adapter.write_error("Execution failed.\n");
                break;
            case EXECCP:
                session_adapter.write_error("Execution completed.\n");
                break;
            case INVARG:
                session_adapter.write_error("Invalid arguments.\n");
                break;
            default:
                session_adapter.write_error("Some strange error.\n");
        }
        return EXECCP;
    }
}
