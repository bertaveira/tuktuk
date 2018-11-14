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
  FILE *fp = NULL, *fpw = NULL;
  char *outfilename = NULL, *aux;

  if (argc < 2)
    return(0);
  fp = fopen(argv[1], "r");
  outfilename = (char *) malloc(sizeof(char)*(strlen(argv[1])));
  nullCheck((Item *) outfilename);
  strcpy(outfilename, argv[1]);
  aux = strrchr(outfilename, '.');
  *aux = '\0';
  strcat(outfilename, ".valid");
  fpw = fopen(outfilename, "w");

  while (( mp = readMap(fp)) != NULL) {
    switch (getMode(mp)) {
      case 'A':
        modeVarA(mp, fpw);
        break;
      case 'B':

        break;
    }
  }


  fclose(fp);

}
