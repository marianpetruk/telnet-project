#include "Mpwd.h"


namespace myshell {
    void Mpwd::show_help() {
        std::cout << "Usage: mpwd [-h|--help]" << std::endl;
    }

    int Mpwd::execute_command(const std::vector<std::string> &argv) {
        try {
            if (argv.size() > 1) {
                std::cerr << "Too many arguments" << std::endl;
                return INVARG;
            }
            else {
                std::cout << syscalls::get_working_directory() << std::endl;
                return EXECCP;
            }
        }
        catch (syscalls::SystemCallError &e) {
            std::cerr << e.what() << std::endl;
            return EXECFD;
        }
    }
}
