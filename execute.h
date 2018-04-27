#ifndef ECHOSERVER_EXECUTE_H
#define ECHOSERVER_EXECUTE_H


#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

int execute(std::vector<std::string> &argv, int fd);

#endif //ECHOSERVER_EXECUTE_H
