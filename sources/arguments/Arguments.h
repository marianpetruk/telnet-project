#ifndef MYSHELL_ARGUMENTS_H
#define MYSHELL_ARGUMENTS_H


#include <vector>
#include <string>
#include <iostream>

#include "DescriptorChanger.h"

namespace arguments {
    class Arguments {
    private:
        std::vector<std::string> argv;
        std::vector<DescriptorChanger> redirects;
        bool fone;

    public:
        void add_redirect(const std::string &redirect);

        void add_arg(const std::string &arg);

        const std::vector<std::string> &get_argv() const;

        void set_argv(const std::vector<std::string> &argv);

        const std::vector<DescriptorChanger> &get_redirects() const;

        void set_redirects(const std::vector<DescriptorChanger> &redirects);

        bool is_fone() const;

        void set_fone(bool fone_execution);

        void print_info();
    };
}


#endif //MYSHELL_ARGUMENTS_H
