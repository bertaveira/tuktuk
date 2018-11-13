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
  nullCheck(mp);
  //read first line
  a = fscanf(fp, "%d %d %c %d", mp->y, mp->x, mp->mode, mp->nPoints);
  //alloc space for points
  mp->points[0] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck(mp->points[0]);
  mp->points[1] = (int *)malloc(sizeof(int)* mp->nPoints);
  nullCheck(mp->points[1]);

  //save the points given
  for(i = 0; i < mp->nPoints; i++) {
    a = fscanf(fp, "%d %d", y, x);
    mp->points[0][i] = y;
    mp->points[1][i] = x;
  }
  //map => mp->map[x][y]
  mp->map = (int **)malloc(sizeof(*int)*mp->x);
  nullCheck(mp->map);

  for(i = 0; i < mp->x; i++) {
    mp->map[i] = (int *)malloc(sizeof(int)*mp->y);
    nullCheck(mp->map[i]);
    //fill matrix with cost
    for(j = 0; j < mp->y; j++){
      a = fscanf(fp, "%d", mp->map[i][j])
    }
  }

  return mp;
}
