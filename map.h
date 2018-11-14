#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"

typedef struct _map map;

map* readMap(FILE *);
int varA (map *, int, int);
void compA (map *, int, int, int *);
int inMapCheck (map *, int, int);
char getMode(map *);
char getPOI(map *, int, int);
void modeVarA(map *, FILE *);

#endif
