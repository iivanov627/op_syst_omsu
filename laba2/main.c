#include <stdio.h>

#include "cat.h"
#include "input.h"

int main(int argc, char *argv[]) {
  struct s_flags flags = input(argc, argv);
  int line_count = 1;

  if (flags.error) {
    printf("Error\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') continue;
    cat(flags, argv[i], &line_count);
  }

  return 0;
}
