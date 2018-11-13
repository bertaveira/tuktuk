#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "funcs.h"

void nullCheck(Item* i) {
  if ( i == NULL) {
    printf("erro de alocação\n");
    exit(0);
  }
}
