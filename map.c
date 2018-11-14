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
in:
  mp -- city map
  x and y -- coordinats of starting position
out:
  int: 0 if not posible
       >0 minimal cost jump
internal:
  auxx,auxy -- ints to store new possibel possition
  min -- cost of the lowst cost possition to date
  minx, miny -- coordinats of the minimal cost possition to date
*/
short int varA (map *mp, short int x, short int y){
  if(inMapCheck(mp, x, y) == 0){
    return 0;
  }
  short int auxx, auxy, min = -1;
  auxx = x-2;
  auxy = y-1;
  compA(mp, auxx, auxy, &min);
  auxy = y+1;
  compA(mp, auxx, auxy, &min);
  auxx = x+2;
  compA(mp, auxx, auxy, &min);
  auxy = y-1;
  compA(mp, auxx, auxy, &min);
  auxx = x+1;
  auxy = y+2;
  compA(mp, auxx, auxy, &min);
  auxy = y-2;
  compA(mp, auxx, auxy, &min);
  auxx = x-1;
  compA(mp, auxx, auxy, &min);
  auxy = y+2;
  compA(mp, auxx, auxy, &min);
  if(min != -1)
    return min;
  return 0;
}


/*
in: mp -- map of city
    newx, newy -- new coordinats to compare
    minx, miny -- coordinats of minnimal cost
    min -- cost of minimal cost position to date
*/
void compA (map *mp, short int newx, short int newy, short int *min){
  if (inMapCheck(mp, newx, newy) == 1){
    if (*min > mp->map[newy][newx] || *min == -1){
      *min = mp->map[newy][newx];
    }
  }
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

void modeVarA(map *mp, FILE *fpw){
  short int res = 0, aux = -1;

  if(mp->nPoints == 1)
    res = varA(mp, getPOI(mp, 1, 0), getPOI(mp, 0, 0));
  if(res != 0) aux = 1;
  fprintf(fpw, "%d %d %c %d %d %d\n\n", mp->y, mp->x, mp->mode, mp->nPoints, aux, res);
}


short int validMove(map *mp, short int i) {
  short int x, y;
  if(inMapCheck(mp, mp->points[1][i], mp->points[0][i]) == 0) {
    return 0;
  } else {
    if (i < 1) return 1;
    x =  mp->points[1][i] -mp->points[1][i-1];
    y =  mp->points[0][i] -mp->points[0][i-1];
    if ( abs(x) + abs(y) == 3 && (x != 0) && (y != 0)) return 1;
    else return 0;
  }
}


void modeVarB(map *mp, FILE *fpw){
  short int aux = -1, sum = 0;

  for(int i = 0; i < mp->nPoints; i++){
    if( validMove(mp, i) ){
      if(i>0){
        sum = sum + mp->map[mp->points[0][i]][mp->points[1][i]];
      }
    }else{
      sum = 0;
      break;
    }
  }

  if(sum != 0) aux = 1;
  fprintf(fpw, "%d %d %c %d %d %d\n\n", mp->y, mp->x, mp->mode, mp->nPoints, aux, sum);
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
