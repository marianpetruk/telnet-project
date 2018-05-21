#include "Myshell.h"


namespace myshell{
    void Myshell::show_help() {
        std::cout << "Usage: myshell [filename] [-h|--help]" << std::endl;
    }

    int Myshell::execute_command(const std::vector<std::string> &argv) {
        if (argv.size() > 2) {
            std::cerr << "Invalid number of arguments" << std::endl;
            return INVARG;
        }

        vm::VariablesMap variablesMap;

        // UPDATE PATH
        std::string path = dirname(realpath(argv[0].c_str(), nullptr));
        std::string new_path_var(variablesMap.get("PATH") + ":" + path);
        variablesMap.set("PATH", new_path_var.c_str());

        // CREATE INTERPRETER
        myshell::Interpreter interpreter(variablesMap);
        const std::map<std::string, myshell::Executor*> builtins = {
                {"merrno",   new myshell::Merrno(interpreter)},
                {"mpwd",     new myshell::Mpwd()},
                {"mcd",      new myshell::Mcd()},
                {"mexit",    new myshell::Mexit()},
                {".",        new myshell::FileInterpreter(interpreter)},
                {"mecho",    new myshell::Mecho()},
                {"mexport",  new myshell::Mexport(interpreter)}
        };
        interpreter.set_builtins(builtins);
        if (argv.size() == 2) {
            return builtins.find(".")->second->execute(argv);
        }

        std::string username = variablesMap.get("USER");
        std::string line;
        std::cout << username << ":" << syscalls::get_working_directory() << ": ";
        while (std::getline(std::cin, line)) {
            interpreter.interpret(line);
            std::cout << username << ":" << syscalls::get_working_directory() << ": ";
        }
    }

    void Myshell::run(int argc, char *argv[]) {
        std::vector<std::string> vector;
        for (int i = 0; i < argc; ++i) {
            vector.emplace_back(argv[i]);
        }
        execute(vector);
    }
}
