#include "Mexit.h"


namespace myshell {
    void Mexit::show_help() {
        std::cout << "Usage: mexit [code] [-h|--help]" << std::endl;
    }

    int Mexit::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        try {
            if (argv.size() > 2) {
                session_adapter.write_error("Too many arguments\n");
                return INVARG;
            }
            else {
                exit(argv.size() == 1 ? 0 : std::stoi(argv[1]));
            }
        }
        catch (std::invalid_argument &e) {
            session_adapter.write_error("Invalid argument\n");
            return INVARG;
        }
    }
}
