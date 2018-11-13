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
  char *outfilename = NULL;

  if (argc < 2)
    return(0);
  fp = fopen(argv[1], "r");
  outfilename = (char *) malloc(sizeof(char)*(strlen(argv[1]+srtlen(".coiso"))));
  nullCheck(outfilename);
  strcpy(outfilename, argv[1]);
  strcat(outfilename, ".coiso");
  fpw = fopen(outfilename, "w");

  while (( mp = readMap(fp)) != NULL) {
    switch (getMode(mp)) {
      case 'A':
        compVarA(mp, fpw);
        break;
      case 'B':

        break;
    }
  }


  fclose(fp);

}
