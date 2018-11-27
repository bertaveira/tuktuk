#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"
#include "funcs.h"

typedef struct _map {
  short int ** map;
  short int y;
  short int x;
  char mode;
  short int nPoints;
  short int *points[2];
} map;

typedef struct _node {
  short int cost;
  short int org[2];
} node;


map* readMap(FILE * fp) {
  short int a = 0, i, x, y, j;

  //struct that contains the map and all the parameters
  map *mp = (map *)malloc(sizeof(map));
  nullCheck((Item)mp);
  //read first line
  a = fscanf(fp, "%hd %hd %c %hd", &mp->y, &mp->x, &mp->mode, &mp->nPoints);
  if ( a == EOF) {
    free(mp);
    return NULL;
  }

  //alloc space for points
  mp->points[0] = (short int *)malloc(sizeof(short int)* mp->nPoints);
  nullCheck((Item)mp->points[0]);
  mp->points[1] = (short int *)malloc(sizeof(short int)* mp->nPoints);
  nullCheck((Item)mp->points[1]);

  //save the points given
  for(i = 0; i < mp->nPoints; i++) {
    a = fscanf(fp, "%hd %hd", &y, &x);
    scanCheck(a, 2);
    mp->points[0][i] = y;
    mp->points[1][i] = x;
  }
  //map => mp->map[y][x]
  mp->map = (short int **)malloc(sizeof(short int*)*mp->y);
  nullCheck((Item)mp->map);

  for(i = 0; i < mp->y; i++) {
    mp->map[i] = (short int *)malloc(sizeof(short int)*mp->x);
    nullCheck((Item)mp->map[i]);
    //fill matrix with cost
    for(j = 0; j < mp->x; j++){
      a = fscanf(fp, "%hd", &mp->map[i][j]);
      scanCheck(a, 1);
    }
  }

  return mp;
}



/*
in: mp -- map of city
    x,y -- coordinats to inMapCheck
return: 1 if valid
        0 if unvalid
*/
short int inMapCheck (map *mp, short int x, short int y){
  if (x >= 0 && x < mp->x && y >= 0 && y < mp->y && mp->map[y][x] != 0)
    return 1;
  return 0;
}


char getMode(map * mp) {
  return mp->mode;
}

short int getPOI(map * mp, short int a, short int b) {
  return mp->points[a][b];
}




void modeA(map *mp, FILE *fpw){



}






void modeB(map *mp, FILE *fpw){


}




void freeMap(map *mp){
  free(mp->points[0]);
  free(mp->points[1]);
  for(int i=0; i<mp->y; i++){
    free(mp->map[i]);
  }
  free(mp->map);
  free(mp);
}

void printerror(map * mp, FILE *fpw){
  fprintf(fpw, "%d %d %c %d %d %d\n\n", mp->y, mp->x, mp->mode, mp->nPoints, -1, 0);
}
