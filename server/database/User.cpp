#include "User.h"


namespace server {
    namespace database {
        User::User(std::string n, std::string p) : name(n), password(p) {}
    }
}
