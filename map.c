#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "map.h"
#include "funcs.h"
#include "heap.h"

const short int PF[2][8] = {{-1,1,2,2,1,-1,-2,-2},{-2,-2,-1,1,2,2,1,-1}};

struct _map {
  short int ** map;
  short int y;
  short int x;
  char mode;
  short int nPoints;
  short int *points[2];
};

struct _node {
  short int cost;
  short int org[2];
  short int y;
  short int x;
};

#define DEBUG 0


map* readMap(FILE * fp, int *error) {
  short int a = 0, i, x, y, j;

  //struct that contains the map and all the parameters
  map *mp = (map *)malloc(sizeof(map));
  nullCheck((Item)mp);
  mp->map = NULL;
  mp->points[0] = NULL;
  mp->points[1] = NULL;
  //read first line
  a = fscanf(fp, "%hd %hd %c %hd", &mp->y, &mp->x, &mp->mode, &mp->nPoints);
  if ( a == EOF) {
    free(mp);
    return NULL;
  }
  scanCheck(a, 4);

  if(mp->mode != 'A' && mp->mode != 'B' && mp->mode != 'C'){
    toend(fp, mp);
    return mp;
  }
  if (mp->nPoints < 2 || (mp->mode == 'A' && mp->nPoints != 2)) {
    *error = 1;
    toend(fp, mp);
    return mp;
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
    if(inMapCheck(mp,x, y) == 0) *error = 1;
  }
  if (*error == 1) {
    toend(fp, mp);
    return mp;
  }
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

  for(i = 0; i<mp->nPoints; i++){
    if(inMapCheck(mp, mp->points[1][i], mp->points[0][i]) == 0) {
      *error = 1;
      return mp;
    }
  }

  return mp;
}



void modeA(map *mp, FILE *fpw){
  list *lt;
  int count = 0;

  // find best path
  lt = shortestPath(mp, 0, 1, 0);
  //print first line of output file
  fprintf(fpw, "%hd %hd %c %hd ", mp->y, mp->x, mp->mode, mp->nPoints );
  // found path or not
  if( lt == NULL) fprintf(fpw, "-1 0\n\n");
  else {
    fprintf(fpw, "%hd ", ((node *)(lt->item))->cost); // print total cost
    clearList(lt);
    printPoints(lt, fpw, &count, mp); // print list of points of best path
    fprintf(fpw, "\n");
  }
  freeList(lt);
}


void modeB(map *mp, FILE *fpw){
  int i, count = 0;
  list *lt = NULL, *aux = NULL;

  lt = shortestPath(mp, 0, 1, 0);
  clearList(lt);
  // find best path
  for (i = 2; i < mp->nPoints; i++) {
    aux = (list *)shortestPath(mp, i-1, i, ((node *)(lt->item))->cost);
    clearList(aux);
    lt = (list *)mergeLists(aux, lt);
    if (lt == NULL) break;
  }
  //print first line of output file
  fprintf(fpw, "%hd %hd %c %hd ", mp->y, mp->x, mp->mode, mp->nPoints );
  // found path or not
  if( lt == NULL) fprintf(fpw, "-1 0\n\n");
  else {
    fprintf(fpw, "%hd ", ((node *)(lt->item))->cost); // print total cost
    printPoints(lt, fpw, &count, mp); // print list of points of best path
    fprintf(fpw, "\n");
  }
  freeList(lt);
}



/**
*  - modeC - Run variable C of the program
*
* @param map *mp - structure with map of cost, size of board and points of interest
* @param FILE *fpw - file to output to
*
**/
void modeC(map *mp, FILE *fpw){
  list ***adj = (list ***)malloc(sizeof(list **)*mp->nPoints); // matrix of paths between two points
  list *lt = NULL;
  int i, j, cost = 0, count = 0;
  int best[mp->nPoints], vect[mp->nPoints]; // best path and path being examined

  // each list stores the best path between two points (adj[a][b] - path a->b)
  for(i=0; i<mp->nPoints; i++) adj[i] = (list **)malloc(sizeof(list *)*mp->nPoints);
  for( i = 0; i<mp->nPoints; i++) {
    adj[i][i] = NULL;
    for (j = i+1; j<mp->nPoints; j++) {
      adj[i][j] = shortestPath(mp, i, j, 0); // get best path between points i and j (from mp->points[][x])
      clearList(adj[i][j]); // remove from list the points no in best path
      // backwords path set to NULL (later if needed we can reverse the list)
      adj[j][i] = NULL;
    }
  }
  //start point is 0
  vect[0] = 0; // each number "x" coresponds to the point (mp->points[1][x], mp->points[0][x])
  // call recursive function to find best hamilton path between the points of interest
  hamAndCheese(1, mp, adj, vect, best, 0, &cost);
  if(DEBUG) printf("A very nice ham indeed\n");

  // no possible path
  if( cost == 0 ) {
    printerror(mp, fpw);
    freeAdj(adj, mp->nPoints);
    return;
  }
  if(DEBUG) printf("melt that cheese\n");
  printf("saiu\n");

  // merge all the lists of paths between points to form the best overall path
  for (i = 0; i<mp->nPoints-1; i++) {
    // list backwords... need to reverse it
    if (adj[vect[i]][vect[i+1]] == NULL) {
      adj[vect[i]][vect[i+1]] = reverseList(adj[vect[i+1]][vect[i]], mp, vect[i+1]);
      adj[vect[i+1]][vect[i]] = NULL; // prevent future errors by assaining null
    }
    // transfer list to the mega list
    lt = (list *)mergeLists(adj[vect[i]][vect[i+1]], lt);
  }
  nullCheck(lt);

  //remove vertices from the adj matrix to prevent double frees
  for (i = 1; i<mp->nPoints; i++) {
    adj[vect[i-1]][vect[i]] = NULL;
    adj[vect[i]][vect[i-1]] = NULL;
  }
  if(DEBUG) printf("DAMN\n");
  // Print output file
  fprintf(fpw, "%hd %hd %c %hd %d ", mp->y, mp->x, mp->mode, mp->nPoints, cost);
  printPoints(lt, fpw, &count, mp);
  fprintf(fpw, "\n");
  // free all
  freeList(lt);
  freeAdj(adj, mp->nPoints);
}


/**
*  - hamAndCheese - Recursive function to find best hamilton path (taking cost into consideration)
                    Each recursive call is a position in the intended path (from 0 to nPoints) where each vertice only appears once
*
* @param int pos - position in the vector that we are tying to find a vertice to (increments each recursive call)
* @param map *mp - structure with map of cost, size of board and points of interest
* @param list ***adj - matrix of pointers to the lists of the paths between those 2 points (adj[a][b] - best path bettween a and b represented as a list)
* @param int vect[] - vector that stores the current path being examined (each position is a vertice)
* @param int best[] - vector that stores the best path
* @param int cost - stores the current cost of the path being examined
* @param int bCost - stores the cost of the best path sored in best[]
*
**/
void hamAndCheese(int pos, map *mp, list ***adj, int vect[], int best[], int cost, int *bCost) {
  int i, j, nextCost= 0;

  // found a possible path
  if( pos == mp->nPoints) {
    if(DEBUG) printf("Encontrou um caminho\n");
    // compare the cost with prevous path to find the best
    if (*bCost == 0 || cost < *bCost) {
      if(DEBUG) printf("O caminho e o melhor ate agora\n");
      for (i= 0; i<mp->nPoints; i++)
        best[i] = vect[i];
      *bCost = cost;
    }
    return;
  }
  if(DEBUG) {
    printf("Vetor bef -");
    for (i = 0; i< pos; i++) printf(" %d |", vect[i]);
    printf("\n");
  }
  // find next vertice to assign to vect[pos]
  for (i = 1; i< mp->nPoints; i++) {
    if(cost>=*bCost && *bCost != 0) return;
    // is it already in vect[]? and is it a possible path?
    if ( newAdj(vect, pos, i) && (adj[vect[pos-1]][i] != NULL || adj[i][vect[pos-1]] != NULL)) {
      vect[pos] = i;
      if (adj[vect[pos-1]][i] == NULL) { // path needs to be reversed
        nextCost = cost + ((node *)(adj[vect[i]][pos-1]->item))->cost - mp->map[mp->points[0][vect[pos-1]]][mp->points[1][vect[pos-1]]] + mp->map[mp->points[0][i]][mp->points[1][i]];
      } else nextCost = cost + ((node *)(adj[vect[pos-1]][i]->item))->cost;
      // call itself to finde next step (vect[pos+1])
      hamAndCheese(pos+1, mp, adj, vect, best, nextCost, bCost);
      if(DEBUG) {
        printf("Regrediu\n");
        printf("Vetor -");
        for (j = 0; j<= pos; j++) printf(" %d |", vect[j]);
        printf("\n");
      }
    }
    if(DEBUG) printf("%d- nao satifaz if\n", i);
  }
  return;
}

/**
*  - newAdj - verify if vertice "i" is already in vect[]
*
* @param int vect[] - vector that stores the current path being examined (each position is a vertice)
* @param int pos - position in the vector that we are tying to find a vertice to (increments each recursive call)
* @param int i - vertice to be examined
*
* @return "true2 if it is new and "false" if it was already used
**/
bool newAdj(int vect[], int pos, int i) {
  int j;
  for (j = 1; j<pos; j++)
    if(vect[j] == i ) return false;
  return true;
}

/**
*  - reverseList - reverse the list order to be used backwards
*
* @param list *lt - list to be reversed
* @param map *mp - structure with map of cost, size of board and points of interest
* @param int pos - position of the first vertice (to be added since it is not in the list)
*
**/
list *reverseList(list *lt, map *mp, int pos) {
  if (lt == NULL) return lt;
  int cost = ((node*)(lt->item))->cost - mp->map[((node*)(lt->item))->y][((node*)(lt->item))->x];
  list *aux = lt->next, *next, *prev = lt;
  //delete first point
  prev->next = NULL;
  freeList(prev);
  prev = aux;
  if(aux != NULL) {
    aux = aux->next;
    prev->next = NULL;
  }
  //reverse list
  while (aux != NULL) {
    next = aux->next;
    aux->next = prev;
    prev = aux;
    aux = next;
  }
  //add last point missing from list
  aux = (list*)malloc(sizeof(list));
  aux->item = (node*)malloc(sizeof(node));
  ((node*)(aux->item))->cost = mp->map[mp->points[0][pos]][mp->points[1][pos]] + cost;
  ((node*)(aux->item))->y = mp->points[0][pos];
  ((node*)(aux->item))->x = mp->points[1][pos];
  aux->next = prev;
  return aux;
}


/**
*  - freeAdj - free matrix of lists
*
* @param list ***adj - matrix of pointers to the lists of the paths between those 2 points (adj[a][b] - best path bettween a and b represented as a list)
* @param int n - number width and height of matrix
*
**/
void freeAdj(list ***adj, int n) {
  int i, j;

  for(i = 0; i<n; i++) {
    for(j = 0; j <n; j++) {
      if(adj[i][j] != NULL) freeList(adj[i][j]);
    }
    free(adj[i]);
  }
  free(adj);
}


/**
*in: mp -- map of city
*    x,y -- coordinats to inMapCheck
*return: 1 if valid
*        0 if unvalid
**/
short int inMapCheck (map *mp, short int x, short int y){
  if (x >= 0 && x < mp->x && y >= 0 && y < mp->y && (mp->map == NULL || mp->map[y][x] != 0))
    return 1;
  return 0;
}


char getMode(map * mp) {
  return mp->mode;
}

short int getPOI(map * mp, short int a, short int b) {
  return mp->points[a][b];
}


void clearList(list *lt) {
  list *aux = lt, *trash;
  int x, y;

  if (lt == NULL) return;

  y = ((node *)(lt->item))->org[0];
  x = ((node *)(lt->item))->org[1];

  while (aux->next != NULL) {
    if (y == ((node *)(aux->next->item))->y && x == ((node *)(aux->next->item))->x && ((node *)(aux->next->item))->org[0] != -1) {
      y = ((node *)(aux->next->item))->org[0];
      x = ((node *)(aux->next->item))->org[1];
      aux = aux->next;
    } else {
      trash = aux->next;
      aux->next = trash->next;
      free(trash->item);
      free(trash);
    }
  }
}



void printPoints(list *lt, FILE *fpw, int *count, map *mp) {
  int cost;

  *count = *count +1; //count number of points
  if (lt->next != NULL) {
    printPoints(lt->next, fpw, count, mp); // recursive call
  } else {
    if (((node *)(lt->item))->org[0] != -1){
      fprintf(fpw, "%d\n", *count); // print number of points ate the end of the recurssion
    }else{
      fprintf(fpw, "0\n"); // print number of points ate the end of the recurssion
      return;
    }
  }
  cost = mp->map[((node *)(lt->item))->y][((node *)(lt->item))->x];
  fprintf(fpw, "%hd %hd %hd\n", ((node *)(lt->item))->y, ((node *)(lt->item))->x, cost); //print points
}



list *shortestPath(map *mp, int a, int b, int cost) {
  int i, j;
  bool **mtx;
  node *st = (node *)malloc(sizeof(node));
  list *lt, *aux;

// fazer para coisas com um unico passo--------------------------------------------------------
  i = checkSimplePaths(mp, a, b);
  st->cost = cost;
  st->org[0] = -1;
  st->org[1] = -1;
  st->y = mp->points[0][a];
  st->x = mp->points[1][a];
  // first 2 nodes
  lt = (list *)malloc(sizeof(list));
  lt->item = st;
  lt->next = NULL;

  if ( i == 0 ) {
    return lt;
  } else if (i == 1) {
    aux = (list *)malloc(sizeof(list));
    nullCheck(aux);
    aux->next = lt;
    st = (node *)malloc(sizeof(node));
    st->cost = mp->map[mp->points[0][b]][mp->points[1][b]];
    st->org[0] = mp->points[0][a];
    st->org[1] = mp->points[1][a];
    st->y = mp->points[0][b];
    st->x = mp->points[1][b];
    aux->item = st;
    lt = aux;
    return lt;
  }
  mtx = (bool **)malloc(sizeof(bool *)*mp->y);
  for(i = 0; i< mp->y; i++) {
    mtx[i] = (bool *)malloc(sizeof(bool)*mp->x);
    for(j = 0; j<mp->x; j++) {
      mtx[i][j] = 0;
    }
  }
  mtx[st->y][st->x] = 1;
  heapInit((mp->x*mp->y)/2);
  // start searching for the best path
  while (st != NULL && (st->y != mp->points[0][b] || st->x != mp->points[1][b])) {
    addNodes(mp, st, mtx);
    st = heapGetMax(compNodes);
    aux = (list *)malloc(sizeof(list));
    nullCheck(aux);
    aux->next = lt;
    aux->item = st;
    lt = aux;
  }
  freeHeap();
  //free list of path not found
  if (st == NULL) {
    freeList(lt);
    lt = NULL;
  }
  freeMtx(mtx, mp->y);
  return lt;
}


int checkSimplePaths(map *mp , int a, int b) {
  if (mp->points[0][a] == mp->points[0][b] && mp->points[1][a] == mp->points[1][b]) return 0;
  if ( validMove(mp, b) == 1) return 1;
  return -1;
}

short int validMove(map *mp, short int i) {
  short int x, y;
  x =  mp->points[1][i] -mp->points[1][i-1];
  y =  mp->points[0][i] -mp->points[0][i-1];
  if ( abs(x) + abs(y) == 3 && (x != 0) && (y != 0)) return 1;
  else return 0;
}


void freeMtx(bool **mtx, int y) {
  int i;
  for (i = 0; i<y; i++)
    free(mtx[i]);
  free(mtx);
}

void addNodes(map *mp, node *org, bool **mtx) {
  int i, x, y;
  node *new;

  for(i = 0; i<8; i++) {
    x= org->x +PF[1][i];
    y= org->y +PF[0][i];
    if( inMapCheck(mp, x, y) ) {
      if(mtx[y][x] == 0) {
        new = (node *)malloc(sizeof(node));
        new->y = y;
        new->x = x;
        new->org[0] = org->y;
        new->org[1] = org->x;
        new->cost = org->cost + mp->map[y][x];
        mtx[y][x] = 1;
        heapInsert(new, compNodes);
      }
    }
  }
}



list *mergeLists(list *a, list *b) {
  list *aux = a;

  if (a == NULL) {
    freeList(b);
    return a;
  }
  while ( aux != NULL) {
    if (aux->next == NULL) {
      aux->next = b;
      return a;
    } else aux = aux->next;
  }
  return a;
}

int compNodes(Item a, Item b) {
  nullCheck(a);
  nullCheck(b);
  if( ((node *)a)->cost > ((node *)b)->cost) return 0;
  else return 1;
}



void freeMap(map *mp){
  if (mp->points[0] != NULL ) free(mp->points[0]);
  if (mp->points[1] != NULL ) free(mp->points[1]);
  if (mp->map != NULL) {
    for(int i=0; i<mp->y; i++){
      free(mp->map[i]);
    }
    free(mp->map);
  }
  free(mp);
}


void freeList(list *lt) {
  list *aux = lt;
  while (aux != NULL) {
    aux = lt->next;
    free(lt->item);
    free(lt);
    lt = aux;
  }
}

void printerror(map * mp, FILE *fpw){
  fprintf(fpw, "%d %d %c %d %d %d\n\n", mp->y, mp->x, mp->mode, mp->nPoints, -1, 0);
}



void toend(FILE *fp, map *mp){
  int i = 0,j = 0;
  int *k = malloc(sizeof(int));
  int *h = malloc(sizeof(int));

  if ( mp->points[0] == NULL) {
    for (i = 0; i < mp->nPoints; i++)
      *k = fscanf(fp, "%d %d", k, h);
  }
  for(i = 0; i < mp->y; i++) {
    for(j = 0; j < mp->x; j++)
      *k = fscanf(fp, "%d", k);
  }
  trash(k);
  trash(h);
}

void trash(int *k) {
  free(k);
}
