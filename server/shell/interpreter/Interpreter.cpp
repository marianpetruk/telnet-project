#include "Interpreter.h"


namespace myshell {
    void Interpreter::set_builtins(const std::map<std::string, myshell::Executor *> new_builtins) {
        builtins = new_builtins;
    }

    void Interpreter::interpret(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        if (argv.empty() || argv[0].empty()) {
            return;
        }

        auto found = builtins.find(argv[0]);
        if (found != builtins.end()) {                      // found builtin function
            session_adapter.MYERRNO = (found->second)->execute(argv, session_adapter);
            return;
        }

        if (argv[0].find('=') != std::string::npos) {       // assigning some variable
            if (argv.size() != 1) {
                session_adapter.MYERRNO = INVARG;
                session_adapter.write_error("Too many arguments for assigning value\n");
            }
            else {
                session_adapter.get_variables_map().set(argv[0]);
            }
        }
        else {
            try {
                session_adapter.MYERRNO = syscalls::execute(argv,
                                            session_adapter.get_variables_map().get_global(),
                                            session_adapter.get_out_descriptor());
            }
            catch (syscalls::SystemCallError &e) {
                session_adapter.MYERRNO = EXECFD;
                session_adapter.write_error("%s\n", e.what());
            }
        }
    }

    void Interpreter::interpret(const std::string &line, SessionAdapter &session_adapter) {
        interpret(get_args(line, session_adapter.get_variables_map()), session_adapter);
    }
}
