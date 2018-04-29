#include "Mecho.h"


namespace myshell {
    void Mecho::show_help() {
        std::cout << "Usage: mecho [arg1] [arg2] ... [-h|--help]" << std::endl;
    }

    int Mecho::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        for (auto val = argv.begin() + 1; val < argv.end(); ++val) {
            session_adapter.write("%s ", val->c_str());
        }
        session_adapter.write("\n");
        return EXECCP;
    }
}
