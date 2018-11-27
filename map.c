#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"
#include "funcs.h"

#define PF {{-1,1,2,2,1,-1,-2,-2}, {-2,-2,-1,1,2,2,1,-1}}

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
  short int y;
  short int x;
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



void shortestPath(map *mp, int b, int a) {
  int i, j;
  node ***mtx = (node ***)malloc(sizeof(node**)*mp->y);
  node *st = (node *)malloc(sizeof(node));

  for(i = 0; i< mp->y; i++) {
    mtx[i] = (node **)malloc(sizeof(node*)*mp->x);
    for(j = 0; j<mp->x; j++) {
      mtx[i][j] = NULL;
    }
  }
  st->cost = 0;
  st->org[0] = -1;
  st->org[1] = -1;
  st->y = mp->points[0][a];
  st->x = mp->points[1][a];

  while (st != mtx[mp->points[0][b]][mp->points[1][b]]) {
    addNodes(mp, st, mtx);
    st = heapGetMax();
  }
}


void addNodes(map *mp, node org, node ***mtx) {
  int i;
  node *new;

  for(i = 0; i<8; i++) {
    if( inMapCheck(mp, org[1]+PF[1][i], org[0]+PF[0][i]) ) {
      new = (node *)malloc(sizeof(node));
      new->y = org[0]+PF[0][i];
      new->x = org[1]+PF[1][i];
      new->org[0] = org->y;
      new->org[1] = org->x;
      new->cost = org->cost + mp->map[new->y][new->x];
      heapInsert(new);
    }
  }
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
