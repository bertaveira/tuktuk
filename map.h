#ifndef _MAP_H_
#define _MAP_H_

#include "defs.h"

typedef struct _map map;
typedef struct _node node;


map* readMap(FILE * fp, int *error);
short int inMapCheck (map *mp, short int x, short int y);
char getMode(map * mp);
short int getPOI(map * mp, short int a, short int b);
void modeA(map *mp, char *outname);
void hamAndCheese(int pos, map *mp, list ***adj, int vect[], int best[], int cost, int *bCost);
void clearList(list *lt);
void printPoints(list **lt,list *lt2, FILE *fpw, int *count, map *mp, int);
list *shortestPath(map *mp, int a, int b, int cost);
int checkSimplePaths(map *mp , int a, int b);
short int validMove(map *mp, short int i);
bool movePossible(int ax, int ay, map *mp);
void freeMtx(bool **mtx, int y);
void addNodes(map *mp, node *org, bool**mtx);
void modeB(map *mp, char *outname);
void modeC(map *mp, char *outname);
list *mergeLists(list *a, list *b);
int compNodes(Item a, Item b);
void freeMap(map *mp);
void printerror(map * mp, FILE *fpw);
void freeList(list *lt);
void toend(FILE*, map *);
void trash(int *k);
bool newAdj(int vect[], int a, int i);
list *reverseList(list *lt, map *mp, int pos);
void freeAdj(list ***adj, int n);


#endif
