#ifndef ECHOSERVER_SESSIONADAPTER_H
#define ECHOSERVER_SESSIONADAPTER_H


#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "variable_map/VariablesMap.h"

class SessionAdapter {
private:
    int out_descriptor = STDOUT_FILENO;
    vm::VariablesMap variables_map;

public:
    int MYERRNO = 0;

    void write(const char* message, ...);
    void write(std::string &message, ...);
    void write_error(const char* message, ...);
    void write_error(std::string &message, ...);

    void close_session(int exit_code);

    void set_out_descriptor(int new_descriptor);
    int get_out_descriptor();

    vm::VariablesMap& get_variables_map();
};

class CloseSession : std::exception {
public:
    const char *what() const throw();
};

#endif //ECHOSERVER_SESSIONADAPTER_H
