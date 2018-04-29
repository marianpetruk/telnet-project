#include "VariablesMap.h"


extern char** environ;

namespace vm {
    VariablesMap::VariablesMap() {
        // Copy environ
        for (char** ep = environ; *ep != NULL; ++ep) {
            std::string variable(*ep);
            auto pos = variable.find('=');
            std::string key = variable.substr(0, pos);
            std::string val = variable.substr(pos + 1);
            variables[key] = val;
            global_variables.insert(key);
        }
    }

    bool VariablesMap::contains(const std::string &key) {
        return variables.find(key) != variables.end();
    }

    std::string VariablesMap::get(const std::string &key) {
        auto found = variables.find(key);
        if (found == variables.end()) {
            throw VariablesMapError(key);
        }
        return found->second;
    }

    void VariablesMap::set(const std::string &value) {
        auto pos = value.find('=');
        if (pos == std::string::npos) {
            throw VariablesMapError(value);
        }
        set(value.substr(0, pos), value.substr(pos + 1));
    }
    void VariablesMap::set(const std::string &key, const std::string &value) {
        variables[key] = value;
    }

    void VariablesMap::add_to_global(const std::string &key) {
        if (contains(key)) {
            global_variables.insert(key);
        }
        else {
            throw VariablesMapError(key);
        }
    }

    std::map<std::string, std::string> VariablesMap::get_global() {
        std::map<std::string, std::string> result;
        for (auto &val : variables) {
            if (global_variables.find(val.first) != global_variables.end()) {
                result[val.first] = val.second;
            }
        }
        return result;
    }
}
