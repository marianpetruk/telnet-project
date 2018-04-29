#include "Mexport.h"


namespace myshell {
    void Mexport::show_help() {
        std::cout << "Usage: mexport <variable> [-h|--help]" << std::endl;
    }

    int Mexport::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        if (argv.size() != 2) {
            session_adapter.write_error("Invalid arguments\n");
            return INVARG;
        }
        try {
            std::string value = argv[1];
            auto pos = value.find('=');
            if (value.find('=') != std::string::npos) {     // assigning new value
                session_adapter.get_variables_map().set(value);
                value = value.substr(0, pos);
            }
            session_adapter.get_variables_map().add_to_global(value);
            return EXECCP;
        }
        catch (vm::VariablesMapError &e) {
            session_adapter.write_error("%s\n", e.what());
            return EXECFD;
        }
    }
}
