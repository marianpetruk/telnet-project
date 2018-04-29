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
                std::string new_path = session_adapter.get_variables_map().get("PWD") + "/" + argv[1];
                session_adapter.get_variables_map().set("PWD", syscalls::real_path(new_path));
                return EXECCP;
            }
        }
        catch (syscalls::SystemCallError &e) {
            session_adapter.write_error("%s\n", e.what());
            return EXECFD;
        }
    }
}
