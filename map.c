#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"
#include "funcs.h"

typedef struct _map {
  int ** map;
  int y;
  int x;
  char mode;
  int nPoints;
  int *points[2];
} map;


map* readMap(FILE * fp) {
  int a = 0, i, x, y, j;

  //struct that contains the map and all the parameters
  map *mp = (map *)malloc(sizeof(map));
  nullCheck((Item)mp);
  //read first line
  a = fscanf(fp, "%d %d %c %d", &mp->y, &mp->x, &mp->mode, &mp->nPoints);
  scanCheck(a, 4);
  //alloc space for points
  mp->points[0] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck((Item)mp->points[0]);
  mp->points[1] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck((Item)mp->points[1]);

  //save the points given
  for(i = 0; i < mp->nPoints; i++) {
    a = fscanf(fp, "%d %d", &y, &x);
    scanCheck(a, 2);
    mp->points[0][i] = y;
    mp->points[1][i] = x;
  }
  //map => mp->map[x][y]
  mp->map = (int **)malloc(sizeof(int*)*mp->x);
  nullCheck((Item)mp->map);

  for(i = 0; i < mp->x; i++) {
    mp->map[i] = (int *)malloc(sizeof(int)*mp->y);
    nullCheck((Item)mp->map[i]);
    //fill matrix with cost
    for(j = 0; j < mp->y; j++){
      a = fscanf(fp, "%d", &mp->map[i][j]);
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
int varA (map *mp, int x, int y){
  int auxx, auxy, minx = x-2, miny = y-1, min = -1;
  auxx = x-2;
  auxy = y-1;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxy = y+1;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxx = x+2;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxy = y-1;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxx = x+1;
  auxy = y+2;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxy = y-2;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxx = x-1;
  compA(mp, auxx, auxy, &minx, &miny, &min);
  auxy = y+2;
  compA(mp, auxx, auxy, &minx, &miny, &min);
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
void compA (map *mp, int newx, int newy, int *minx, int *miny, int *min){
  if (inMapCheck(mp, newx, newy) == 1){
    if (*min > mp->map[newx][newy] || *min == -1){
      *min = mp->map[newx][newy];
      *minx = newx;
      *miny = newy;
    }
  }
}


/*
in: mp -- map of city
    x,y -- coordinats to inMapCheck
return: 1 if valid
        0 if unvalid
*/
int inMapCheck (map *mp, int x, int y){
  if (x > 0 && x < mp->x && y > 0 && y < mp->y && mp->map[x][y] != 0)
    return 1;
  return 0;

}


char getMode(map * mp) {
  return mp->mode;
}

char getPOI(map * mp, int a, int b) {
  return mp->points[a][b];
}
