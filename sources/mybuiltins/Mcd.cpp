#include "Mcd.h"


namespace myshell {
    void Mcd::show_help() {
        std::cout << "Usage: mcd <path> [-h|--help]" << std::endl;
    }

    int Mcd::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        try {
            if (argv.size() != 2) {
                session_adapter.write_error("Too many arguments\n");
                return INVARG;
            }
            else {
                syscalls::change_directory(argv[1]);
                return EXECCP;
            }
        }
        catch (syscalls::SystemCallError &e) {
            session_adapter.write_error("%s\n", e.what());
            return EXECFD;
        }
    }
}
