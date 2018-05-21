#include "Arguments.h"


namespace arguments {
    void Arguments::add_redirect(const std::string &redirect) {
        redirects.emplace_back(redirect);
    }

    void Arguments::add_arg(const std::string &arg) {
        argv.push_back(arg);
    }

    const std::vector<std::string> &Arguments::get_argv() const {
        return argv;
    }

    void Arguments::set_argv(const std::vector<std::string> &argv) {
        Arguments::argv = argv;
    }

    const std::vector<DescriptorChanger> &Arguments::get_redirects() const {
        return redirects;
    }

    void Arguments::set_redirects(const std::vector<DescriptorChanger> &redirects) {
        Arguments::redirects = redirects;
    }

    bool Arguments::is_fone() const {
        return fone;
    }

    void Arguments::set_fone(bool fone_execution) {
        fone = fone_execution;
    }

	void Arguments::print_info(){
		std::cout<<"---ARGUMENTS INFO---"<<std::endl;
		std::cout<<"Arguments:"<<std::endl;
		for(auto e: argv){
			std::cout<<e<<std::endl;
		}
		std::cout<<"Redirects size: "<<redirects.size()<<std::endl;
		std::cout<<"Is fone: "<<fone<<std::endl;
		std::cout<<"--------------------"<<std::endl;
	}
}
