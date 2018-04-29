#include "Executor.h"


namespace myshell {
    int Executor::execute(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        for (const auto &arg : argv) {
            if (arg == "-h" || arg == "--help") {
                show_help();
                return EXECCP;
            }
        }
        return execute_command(argv, session_adapter);
    }
}
