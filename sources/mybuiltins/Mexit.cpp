#include "Mexit.h"


namespace myshell {
    void Mexit::show_help() {
        std::cout << "Usage: mexit [code] [-h|--help]" << std::endl;
    }

    int Mexit::execute_command(const std::vector<std::string> &argv) {
        try {
            if (argv.size() > 2) {
                std::cerr << "Too many arguments" << std::endl;
                return INVARG;
            } else {
                exit(argv.size() == 1 ? 0 : std::stoi(argv[1]));
            }
        }
        catch (std::invalid_argument &e) {
            std::cerr << "Invalid argument" << std::endl;
            return INVARG;
        }
    }
}
