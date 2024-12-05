#include "data.h"
#include <stdio.h>

int big_endian() {
  unsigned int i = 1;
  const char *p = (char *)&i;
  if (*p) {
    printf("little\n");
    return 1;
  } else {
    printf("big\n");
    return 0;
  }
}

void inplace_swap(int *x, int *y) {
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}