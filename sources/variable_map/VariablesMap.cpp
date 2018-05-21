#include "VariablesMap.h"


extern char** environ;

namespace vm {
    VariablesMap::VariablesMap() {
        for (char** ep = environ; *ep != NULL; ++ep) {
            std::string val(*ep);
            global_vm.insert(val.substr(0, val.find('=')));
        }
    }

    bool VariablesMap::contains(const std::string &key) {
        const char* value = getenv(key.c_str());
        return value != nullptr;
    }

    std::string VariablesMap::get(const std::string &key) {
        const char* value = getenv(key.c_str());
        if (value == nullptr) {
            throw VariablesMapError(key);
        }
        return value;
    }

    void VariablesMap::set(const std::string &key, const std::string &value) {
        if (setenv(key.c_str(), value.c_str(), 1)) {
            throw VariablesMapError(key);
        }
    }

    void VariablesMap::add_to_global(const std::string &key) {
        if (contains(key)) {
            global_vm.insert(key);
        }
        else {
            throw VariablesMapError("key");
        }
    }

    std::vector<std::string> VariablesMap::get_global() {
        std::vector<std::string> result;
        for (char** ep = environ; *ep != NULL; ++ep) {
            std::string val(*ep);
            if (global_vm.find(val.substr(0, val.find('='))) != global_vm.end()) {
                result.push_back(val);
            }
        }
        return result;
    }
}
