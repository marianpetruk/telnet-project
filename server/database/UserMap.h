#ifndef ECHOSERVER_USERMAP_H
#define ECHOSERVER_USERMAP_H


#include <iostream>
#include <map>
#include <fstream>

#include "User.h"

namespace database {
    class UsersMap{
    public:
        std::string fn;
        std::map<std::string, std::string> users_map;

        UsersMap (std::string);

        void write_db();
        bool validate(User);
        bool add_user(User);
        bool remove_user(User);
    };
}


#endif //ECHOSERVER_USERMAP_H
