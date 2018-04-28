#include "Interpreter.h"


namespace myshell {
    void Interpreter::set_builtins(const std::map<std::string, myshell::Executor *> new_builtins) {
        builtins = new_builtins;
    }

    void Interpreter::interpret(const std::vector<std::string> &argv, vm::VariablesMap &variables_map) {
        if (argv.empty() || argv[0].empty()) {
            return;
        }

        auto found = builtins.find(argv[0]);
        if (found != builtins.end()) {                      // found builtin function
            MYERRNO = (found->second)->execute(argv, variables_map);
            return;
        }

        auto pos = argv[0].find('=');
        if (argv[0].find('=') != std::string::npos) {       // assigning some variable
            if (argv.size() != 1) {
                MYERRNO = INVARG;
                std::cerr << "Too many arguments for assigning value" << std::endl;
            }
            variables_map.set(argv[0].substr(0, pos), argv[0].substr(pos + 1));
        }
        else {
            try {
                MYERRNO = syscalls::execute(argv, variables_map.get_global());
            }
            catch (syscalls::SystemCallError &e) {
                MYERRNO = EXECFD;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Interpreter::interpret(const std::string &line, vm::VariablesMap &variables_map) {
        interpret(get_args(line, variables_map), variables_map);
    }
}
