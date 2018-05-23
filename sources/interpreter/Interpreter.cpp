#include "Interpreter.h"


namespace myshell {
    Interpreter::Interpreter(vm::VariablesMap &vm) : variablesMap(vm) {};

    void Interpreter::set_builtins(const std::map<std::string, myshell::Executor *> new_builtins) {
        builtins = new_builtins;
    }

    void Interpreter::interpret(const std::vector<arguments::Arguments> &arguments) {
        if (arguments.empty() || arguments[0].get_argv().empty() || arguments[0].get_argv()[0].empty()) {
            return;
        }

        auto found = builtins.find(arguments[0].get_argv()[0]);
        if (found != builtins.end()) {                      // found builtin function
            MYERRNO = (found->second)->execute(arguments[0].get_argv());
            return;
        }

        auto pos = arguments[0].get_argv()[0].find('=');
        if (arguments[0].get_argv()[0].find('=') != std::string::npos) {       // assigning some variable
            if (arguments[0].get_argv().size() != 1) {
                MYERRNO = INVARG;
                std::cerr << "Too many arguments for assigning value" << std::endl;
            }
            variablesMap.set(arguments[0].get_argv()[0].substr(0, pos), arguments[0].get_argv()[0].substr(pos + 1));
        } else {
            try {
                MYERRNO = syscalls::execute(arguments, variablesMap.get_global());
            }
            catch (syscalls::SystemCallError &e) {
                MYERRNO = EXECFD;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Interpreter::interpret(const std::string &line) {
        //     arguments::Arguments arguments{};
        // 	std::vector<std::string> vct = get_args(line, variablesMap);
        // 	for(auto e: vct){
        // 		std::cout<<e<<std::endl;
        // 	}
        //     arguments.set_argv(vct);
        //    arguments.add_redirect("<koko.txt");
        //    arguments.add_redirect(">koko.txt");
        //    arguments.add_redirect("2>&1");
        //     interpret(arguments);

        std::vector<arguments::Arguments> arguments_vect = get_args(line, variablesMap);
        // TODO: Add | suppor, not only first
        interpret(arguments_vect);
    }
}
