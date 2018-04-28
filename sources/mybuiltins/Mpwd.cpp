#include "Mpwd.h"


namespace myshell {
    void Mpwd::show_help() {
        std::cout << "Usage: mpwd [-h|--help]" << std::endl;
    }

    int Mpwd::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        try {
            if (argv.size() > 1) {
                session_adapter.write_error("Too many arguments");
                return INVARG;
            }
            else {
                std::cout << syscalls::get_working_directory().c_str() << std::endl;
                session_adapter.write("%s\n", syscalls::get_working_directory().c_str());
                return EXECCP;
            }
        }
        catch (syscalls::SystemCallError &e) {
            session_adapter.write_error("%s\n", e.what());
            return EXECFD;
        }
    }
}
