#include "FileInterpreter.h"


namespace myshell {
    FileInterpreter::FileInterpreter(Interpreter &interpreter): interpreter(interpreter) {};

    void FileInterpreter::show_help() {
        std::cout << "Usage: . <filename> [-h|--help]" << std::endl;
    }

    int FileInterpreter::execute_command(const std::vector<std::string> &argv) {
        if (argv.size() != 2) {
            std::cerr << "Invalid number of arguments" << std::endl;
            return INVARG;
        }
        else {
            std::string line;
            std::ifstream file(argv[1]);
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    interpreter.interpret(line);
                }
                file.close();
                return EXECCP;
            } else {
                std::cerr << "Invalid filename: " << argv[1] << std::endl;
                return INVARG;
            }
        }
    }
}