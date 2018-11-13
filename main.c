/******************************************************************************
 *
 * File Name: main.c
 *
 * NAME
 *     main
 *
 * SYNOPSIS
 *		#include <stdlib.h>
 *		#include <stdio.h>
 *		#include <string.h>
 *		#include "word.h"
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS
 *          tested
 *****************************************************************************/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "map.h"
#include "func.h"


int main(int argc, char **argv) {
  FILE *fp = NULL;

  fp = fopen(argv[1], "r");

  while (( mp == readMap(fp)) != NULL) {

  }


  fclose(fp);

}
