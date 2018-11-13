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
#include "funcs.h"


int main(int argc, char **argv) {
  map *mp;
  FILE *fp = NULL;
  int i = 0;

  if (argc < 2)
    return(0);
  fp = fopen(argv[1], "r");

  while (( mp = readMap(fp)) != NULL) {
    switch (getMode(mp)) {
      case 'A':
        i = varA(mp, getPOI(mp, 0, 0), getPOI(mp, 1, 0));
        break;
      case 'B':

        break;
    }
  }


  fclose(fp);

}
