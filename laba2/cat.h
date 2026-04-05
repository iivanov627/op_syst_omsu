#ifndef CAT_H
#define CAT_H
#include <stdio.h>
#include <string.h>

#include "input.h"

void cat(struct s_flags flags, char *path, int *count);
void special_symbol(struct s_flags flags, char buffer[4096]);

#endif