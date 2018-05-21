#ifndef MYSHELL_DESCRIPTORCHANGER_H
#define MYSHELL_DESCRIPTORCHANGER_H


#include <string>

#include "ArgumentsError.h"
#include "../syscalls/systemcalls.h"

namespace arguments {
    class DescriptorChanger {
    private:
        int from;
        std::string to;

    public:
        DescriptorChanger(const std::string &redirect);

        void apply() const;
    };
}


#endif //MYSHELL_DESCRIPTOR_H
