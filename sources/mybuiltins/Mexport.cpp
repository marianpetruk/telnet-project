#include "Mexport.h"


namespace myshell {
    Mexport::Mexport(myshell::Interpreter &interpreter): interpreter(interpreter) {};

    void Mexport::show_help() {
        std::cout << "Usage: mexport <variable> [-h|--help]" << std::endl;
    }

    int Mexport::execute_command(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) {
        if (argv.size() != 2) {
            std::cerr << "Invalid arguments" << std::endl;
            return INVARG;
        }
        try {
            std::string value = argv[1];
            auto pos = value.find('=');
            if (pos != std::string::npos) {     // assigning new value
                variables_map.set(value.substr(0, pos), value.substr(pos + 1));
                value = value.substr(0, pos);
            }
            variables_map.add_to_global(value);
            return EXECCP;
        }
        catch (vm::VariablesMapError &e) {
            std::cerr << e.what() << std::endl;
            return EXECFD;
        }
    }
}
