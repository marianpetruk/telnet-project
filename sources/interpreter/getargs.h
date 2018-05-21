#ifndef MYSHELL_GETARGS_H
#define MYSHELL_GETARGS_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <dirent.h>
#include <libgen.h>
#include <cctype>

#include "../variable_map/VariablesMap.h"
#include "../arguments/Arguments.h"


std::vector<arguments::Arguments> get_args(std::string input, vm::VariablesMap &variables);

#endif //MYSHELL_GETARGS_H
