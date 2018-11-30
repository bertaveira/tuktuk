#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"

typedef struct _map map;


map* readMap(FILE * fp);
short int inMapCheck (map *mp, short int x, short int y);
void modeA(map *mp, FILE *fpw);
void printPoints(list *lt, Filr *fpw, int *count);
list *shortestPath(map *mp, int a);
void addNodes(map *mp, node org, short int mtx[mp->y][mp->x]);
void modeB(map *mp, FILE *fpw);
int compNodes(Item a, Item b);
short int getX(Item a);
short int getY(Item a);
void freeMap(map *mp);
void printerror(map * mp, FILE *fpw);


#endif
