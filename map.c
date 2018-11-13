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


map* readArgs(FILE * fp) {
  int a = 0;

  //struct that contains the map and all the parameters
  map *mp = (map *)malloc(sizeof(map));
  nullCheck(mp);
  //read first line
  a = fscanf(fp, "%d %d %c %d", mp->y, mp->x, mp->mode, mp->nPoints);
  //alloc space for points
  mp->points[0] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck(mp->points[0]);
  mp->points[1] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck(mp->points[1]);

  
}
