#include "Executor.h"


namespace myshell {
    int Executor::execute(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) {
        for (const auto &arg : argv) {
            if (arg == "-h" || arg == "--help") {
                show_help();
                return EXECCP;
            }
        }
        return execute_command(argv, variables_map);
    }
}
