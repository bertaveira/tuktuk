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
  char *outfilename = NULL, *aux = 0;
  int error = 0;

  if (argc < 2)
    return(0);
  fp = fopen(argv[1], "r");
  nullCheck((Item)fp);
  outfilename = (char *) malloc(sizeof(char)*(strlen(argv[1])+1));
  nullCheck((Item) outfilename);
  strcpy(outfilename, argv[1]);
  aux = strrchr(outfilename, '.');
  nullCheck((Item)aux);
  *aux = '\0';
  strcat(outfilename, ".walks\0");
  fpw = fopen(outfilename, "w");

  while (( mp = readMap(fp, &error)) != NULL) {
    if (error == 1) {
      printerror(mp, fpw);
      error = 0;
      continue;
    }
    switch (getMode(mp)) {
      case 'A':
        modeA(mp, fpw);
        freeMap(mp);
        break;
      case 'B':
        modeB(mp, fpw);
        freeMap(mp);
        break;
      default:
        printerror(mp, fpw);
    }
    error = 0;
  }

  free(outfilename);
  fclose(fpw);
  fclose(fp);
  return 0;
}
