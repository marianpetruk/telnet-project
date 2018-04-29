#include "Mpwd.h"


namespace myshell {
    void Mpwd::show_help() {
        std::cout << "Usage: mpwd [-h|--help]" << std::endl;
    }

    int Mpwd::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        if (argv.size() > 1) {
            session_adapter.write_error("Too many arguments\n");
            return INVARG;
        }
        else {
            session_adapter.write("%s\n", session_adapter.get_variables_map().get("PWD").c_str());
            return EXECCP;
        }
    }
}
