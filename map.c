#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"


map* readArgs() {

  fscanf();
}

typedef struct _map {
  int ** map;
  int y;
  int x;
  char mode;
  int nPoints;
  int points *[2];
} map;

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
  int auxx, auxy, min = 0, minx = -1, miny;
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

  if(minx != -1)
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
  if (newx > 0 || newx < map->x || newy > 0 || newy < mp->y){
    if(minx = -1){
      min = mp->map[newx][newy];
      minx = newx;
      miny = newy;
    }else {
      if (mp->map[minx][miny] > mp->map[newx][newy]){
        min = mp->map[newx][newy];
        minx = newx;
        miny = newy;
      }
    }
  }
}
