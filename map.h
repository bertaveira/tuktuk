#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"

typedef struct _map map;

map* readMap(FILE *);
short int varA (map *, short int, short int);
void compA (map *, short int, short int, short int *);
short int inMapCheck (map *, short int, short int);
char getMode(map *);
short int getPOI(map *, short int, short int);
void modeVarA(map *, FILE *);
short int validMove(map *, short int);
void modeVarB(map *, FILE *);
void freeMap(map *);
void printerror(map *,FILE *);

#endif
