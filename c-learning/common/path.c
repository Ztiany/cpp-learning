#include "path.h"
#include <stdio.h>
#include <unistd.h>

int get_pwd(char *pwd, const int length) {
  return getcwd(pwd, length) == NULL ? 0 : 1;
}

void print_pwd() {
  char pwd[251] = {0};
  if (get_pwd(pwd, 250)) {
    printf("current directory: %s", pwd);
  } else {
    printf("the directory couldn't be determined or SIZE was too small");
  }
}
