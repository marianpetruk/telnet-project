#include "UserMap.h"


namespace server {
    namespace database {
        UsersMap::UsersMap(const std::string &filename) : fn(filename) {
            std::string n;
            std::string p;
            std::ifstream infile(filename);
            while (infile >> n >> p) {
                users_map[n] = p;
            }
            infile.close();
        }

        bool UsersMap::validate(const User &user) {
            if (users_map.find(user.name) == users_map.end()) {
                //std::cout << "You are not signed up" << std::endl;
                return false;
            } else {
                return users_map[user.name] == user.password;
            }
        }

        void UsersMap::write_db() {
            std::ofstream outfile;
            outfile.open(fn);
            for (auto &it : users_map) {
                outfile << it.first << " " << it.second << std::endl;
            }
            outfile.close();
        }

        bool UsersMap::add_user(const User &user) {
            this->users_map[user.name] = user.password;
            write_db();
        }

        bool UsersMap::remove_user(const User &user) {
            users_map.erase(user.name);
            write_db();
        }
    }
}
