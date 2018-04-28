#include "Mcd.h"


namespace myshell {
    void Mcd::show_help() {
        std::cout << "Usage: mcd <path> [-h|--help]" << std::endl;
    }

    int Mcd::execute_command(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) {
        try {
            if (argv.size() != 2) {
                std::cerr << "Too many arguments" << std::endl;
                return INVARG;
            }
            else {
                syscalls::change_directory(argv[1]);
                return EXECCP;
            }
        }
        catch (syscalls::SystemCallError &e) {
            std::cerr << e.what() << std::endl;
            return EXECFD;
        }
    }
}
