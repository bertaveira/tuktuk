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

void scanCheck(int a, int b) {
  if ( a != b) {
    printf("erro a ler ficheiro- numero de parametros errado\n");
    exit(0);
  }
}
