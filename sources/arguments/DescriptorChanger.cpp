#include "DescriptorChanger.h"


namespace arguments {
    DescriptorChanger::DescriptorChanger(const std::string &redirect) {
        auto split_pos = redirect.find('>');
        if (split_pos != std::string::npos) {   //changing descriptor
            if (split_pos == 0) {   //changing input
                from = STDOUT_FILENO;
            }
            else {
                try {
                    from = std::stoi(redirect.substr(0, split_pos));
                }
                catch (std::invalid_argument &e) {
                    throw ArgumentsError("Invalid arguments");
                }
            }
        }
        else {
            split_pos = redirect.find('<');
            if (split_pos != std::string::npos) {  // changing input
                from = STDIN_FILENO;
            }
            else {
                throw ArgumentsError("Invalid arguments");
            }
        }
        to = redirect.substr(split_pos + 1);
    }

    void DescriptorChanger::apply() const {
        try {
            if (to[0] == '&') {
                syscalls::change_descriptor(from, std::stoi(to.substr(1)));
            } else {
                int fd = syscalls::open_file(to);
                syscalls::change_descriptor(from, fd);
            }
        }
        catch (std::invalid_argument &e) { // failed to parse
            throw syscalls::SystemCallError(0);
        }
    }
}
