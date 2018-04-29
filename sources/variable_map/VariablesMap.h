#ifndef MYSHELL_MYSHELLVARIABLES_H
#define MYSHELL_MYSHELLVARIABLES_H


#include <algorithm>
#include <vector>
#include <set>
#include <map>

#include "VariablesMapError.h"

namespace vm {
    class VariablesMap {
    private:
        std::map<std::string, std::string> variables;
        std::set<std::string> global_variables;

    public:
        VariablesMap();

        bool contains(const std::string &key);

        std::string get(const std::string &key);

        void set(const std::string &value);
        void set(const std::string &key, const std::string &value);

        void add_to_global(const std::string &key);

        std::vector<std::string> get_global();
    };
}

#endif //MYSHELL_MYSHELLVARIABLES_H
