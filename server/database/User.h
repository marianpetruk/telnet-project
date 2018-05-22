#ifndef ECHOSERVER_USER_H
#define ECHOSERVER_USER_H


#include <string>

namespace database {
    class User {
    public:
        std::string name;
        std::string password;
        User (std::string, std::string);
    };
}


#endif //ECHOSERVER_USER_H
