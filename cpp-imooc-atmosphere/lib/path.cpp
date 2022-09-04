#include "Path.h"
#include <unistd.h>
#include <iostream>

void getPwd(std::string &pwd) {
    if (false) {//不好用
        char *cwd = get_current_dir_name();
        pwd = *cwd;
    } else {
        char buff[250];
        getcwd(buff, 250);
        pwd = buff;
    }
}

void printPwd() {
    std::string result;
    getPwd(result);
    std::cout << "current path: " << result << std::endl;
}