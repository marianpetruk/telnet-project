#include "Mecho.h"


namespace myshell {
    void Mecho::show_help() {
        std::cout << "Usage: mecho [arg1] [arg2] ... [-h|--help]" << std::endl;
    }

    int Mecho::execute_command(const std::vector<std::string> &argv) {
        for (auto val = argv.begin() + 1; val < argv.end(); ++val) {
            std::cout << *val << " ";
        }
        std::cout << std::endl;
        return EXECCP;
    }
}
