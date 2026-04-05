#include "cat.h"

void special_symbol(struct s_flags flags, char buffer[4096]) {
  unsigned char c;

  for (int i = 0; buffer[i] != '\0'; i++) {
    c = (unsigned char)buffer[i];

    if (flags.E && c == '\r') {
      printf("^M");
    } else if (flags.T && c == '\t') {
      printf("^I");
    } else if (flags.E && c == '\n') {
      printf("$\n");
    } else if (flags.v && c < 32 && c != '\n' && c != '\t') {
      printf("^%c", c + 64);
    } else if (flags.v && c == 127) {
      printf("^?");
    } else {
      printf("%c", c);
    }
  }
}

void cat(struct s_flags flags, char *path, int *count) {
  char buffer[4096];
  int prev_empty = 0;
  FILE *fp = fopen(path, "r");

  if (!fp) {
    perror(path);
    return;
  }

  while (fgets(buffer, 4096, fp) != NULL) {
    if (flags.s && strcmp(buffer, "\n") == 0) {
      if (prev_empty) continue;
      prev_empty = 1;
    } else {
      prev_empty = 0;
    }

    if (flags.b && strcmp(buffer, "\n") != 0) {
      printf("%6d\t", (*count)++);
    } else if (flags.n && !flags.b) {
      printf("%6d\t", (*count)++);
    }

    special_symbol(flags, buffer);
  }

  fclose(fp);
}
