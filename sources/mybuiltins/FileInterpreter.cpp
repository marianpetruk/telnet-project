#include "FileInterpreter.h"


namespace myshell {
    FileInterpreter::FileInterpreter(Interpreter &interpreter): interpreter(interpreter) {};

    void FileInterpreter::show_help() {
        std::cout << "Usage: . <filename> [-h|--help]" << std::endl;
    }

    int FileInterpreter::execute_command(const std::vector<std::string> &argv, SessionAdapter &session_adapter) {
        if (argv.size() != 2) {
            session_adapter.write_error("Invalid number of arguments\n");
            return INVARG;
        }
        else {
            std::string line;
            std::ifstream file(argv[1]);
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    interpreter.interpret(line, session_adapter);
                }
                file.close();
                return EXECCP;
            } else {
                session_adapter.write_error("Invalid filename: %s\n", argv[1].c_str());
                return INVARG;
            }
        }
    }
}
