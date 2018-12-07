#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"

typedef struct _map map;
typedef struct _node node;


map* readMap(FILE * fp, int *error);
short int inMapCheck (map *mp, short int x, short int y);
char getMode(map * mp);
short int getPOI(map * mp, short int a, short int b);
void modeA(map *mp, FILE *fpw);
void hamAndCheese(int pos, map *mp, list ***adj, int vect[], int best[], int cost, int *bCost);
void clearList(list *lt);
void printPoints(list *lt, FILE *fpw, int *count, map *mp);
list *shortestPath(map *mp, int a, int b, int cost);
int checkSimplePaths(map *mp , int a, int b);
short int validMove(map *mp, short int i);
void freeMtx(short int **mtx, int y);
void addNodes(map *mp, node *org, short int **mtx);
void modeB(map *mp, FILE *fpw);
void modeC(map *mp, FILE *fpw);
list *mergeLists(list *a, list *b);
int compNodes(Item a, Item b);
short int getX(Item a);
short int getY(Item a);
void freeMap(map *mp);
void printerror(map * mp, FILE *fpw);
void freeList(list *lt);
void toend(FILE*, map *);
void trash(int *k);
bool newAdj(int vect[], int a, int i);


#endif
