#ifndef ECHOSERVER_USERMAP_H
#define ECHOSERVER_USERMAP_H


#include <iostream>
#include <map>
#include <fstream>

#include "User.h"


namespace server {
    namespace database {
        class UsersMap {
        public:
            std::string fn;
            std::map<std::string, std::string> users_map;

            UsersMap(const std::string &);

            void write_db();

            bool validate(const User &);

            bool add_user(const User &);

            bool remove_user(const User &);
        };
    }
}


#endif //ECHOSERVER_USERMAP_H
