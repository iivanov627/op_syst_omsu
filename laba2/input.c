#include "input.h"

void set_flags(char flag, struct s_flags *f) {
  switch (flag) {
    case 'b':
      f->b = 1;
      break;
    case 'E':
      f->E = 1;
      break;
    case 'n':
      f->n = 1;
      break;
    case 's':
      f->s = 1;
      break;
    case 'T':
      f->T = 1;
      break;
    case 'v':
      f->v = 1;
      break;
    case 't':
      f->T = 1;
      f->v = 1;
      break;
    case 'e':
      f->E = 1;
      f->v = 1;
      break;
    default:
      f->error = 1;
  }
}

struct s_flags input(int argc, char *argv[]) {
  struct s_flags f = FLAGS_DEFAULT;

  if (argc < 2) f.error = 1;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') break;

    if (argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0)
        f.b = 1;
      else if (strcmp(argv[i], "--number") == 0)
        f.n = 1;
      else if (strcmp(argv[i], "--squeeze-blank") == 0)
        f.s = 1;
      else
        f.error = 1;
      continue;
    }

    for (int j = 1; argv[i][j] != '\0'; j++) set_flags(argv[i][j], &f);
  }
   return f;
}
