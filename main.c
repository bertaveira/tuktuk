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


int main(int argc, char **argv) {
  FILE *fp = NULL;
  if (argc < 2)
    return(0);
  fp = fopen(argv[1], "r");

  fclose(fp);

}
