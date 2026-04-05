#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLAGS_DEFAULT {0, 0, 0, 0, 0, 0, 0}

struct s_flags {
  int b;
  int E;
  int n;
  int s;
  int T;
  int v;
  int error;
};

struct s_flags input(int argc, char *argv[]);
void set_flags(char flag, struct s_flags *flags);

#endif