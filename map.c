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
  list *lt;
  int count = 0;

  // find best path
  lt = shortestPath(mp, 0);
  //print first line of output file
  fprintf(fpw, "%hd %hd %c %hd", mp->y, mp->x, mp->mode, mp->nPoints );
  // found path or not
  if( lt == NULL) fprintf(fpw, "-1 0\n");
  else {
    fprintf(fpw, "%hd ", ((node *)(lt->item))->cost); // print total cost
    clearList(lt);
    printPoints(lt, fpw, &count); // print list of points of best path
  }

}


void clearList(list *lt) {
  list *aux = lt, *trash;
  int x, y;

  y = ((node *)(lt->item))->org[0];
  x = ((node *)(lt->item))->org[1];

  while (aux->next != NULL) {
    if (y == ((node *)(aux->next->item))->y && x == ((node *)(aux->next->item))->x && ((node *)(aux->next->item))->org[0] != -1) {
      y = ((node *)(aux->next->item))->org[0];
      x = ((node *)(aux->next->item))->org[1];
    } else {
      trash = aux->next;
      aux->next = trash->next;
      free(trash);
    }
    aux = aux->next;
  }
}



void printPoints(list *lt, FILE *fpw, int *count) {
  int cost;

  *count = *count +1; //count number of points
  if (lt->next != NULL) {
    printPoints(lt->next, fpw, count); // recursive call
    cost = ((node *)(lt->item))->cost- ((node *)(lt->next->item))->cost;
  } else {
    fprintf(fpw, "%d\n", *count); // print number of points ate the end of the recurssion
    cost = ((node *)(lt->item))->cost;
  }
  fprintf(fpw, "%hd %hd %hd\n", ((node *)(lt->item))->y, ((node *)(lt->item))->x, cost); //print points
}



list *shortestPath(map *mp, int a) {
  int i, j;
  short int **mtx = (short int **)malloc(sizeof(short int *)*mp->y);
  node *st = (node *)malloc(sizeof(node));
  list *lt, *aux;

// fazer para coisas com um unico passo--------------------------------------------------------
  for(i = 0; i< mp->y; i++) {
    mtx[i] = (short int *)malloc(sizeof(short int)*mp->x);
    for(j = 0; j<mp->x; j++) {
      mtx[i][j] = 0;
    }
  }
  st->cost = 0;
  st->org[0] = -1;
  st->org[1] = -1;
  st->y = mp->points[0][a];
  st->x = mp->points[1][a];
  // first 2 nodes
  lt = (list *)malloc(sizeof(list));
  lt->item = st;
  aux = (list *)malloc(sizeof(list));
  lt->next = aux;
  addNodes(mp, st, mtx);
  st = heapGetMax(mtx, compNodes, getY, getX);
  aux->item = st;
  aux->next = NULL;

  // start searching for the best path
  while (st != NULL && (st->y != mp->points[0][a+1] || st->x != mp->points[1][a+1])) {
    printf("bolachas ");
    addNodes(mp, st, mtx);
    st = heapGetMax(mtx, compNodes, getY, getX);
    aux->next = (list *)malloc(sizeof(list));
    nullCheck(aux->next);
    printf("oreo\n");
    aux = aux->next;
    aux->item = st;
    aux->next = NULL;
  }

  return lt;
}


void addNodes(map *mp, node *org, short int **mtx) {
  int i, x, y, cost;
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
        heapInsert(new, mtx, compNodes, getY, getX);
      } else if (mtx[y][x] > 0) {
        new = getItem(mtx[y][x]);
        cost = org->cost + mp->map[y][x];
        if(new->cost > cost ) {
          new->cost = cost;
          new->org[0] = org->y;
          new->org[1] = org->x;
          Fixup( mtx[y][x] , mtx, compNodes, getY, getX);
        }
      }
    }
  }
}


void modeB(map *mp, FILE *fpw){


}


int compNodes(Item a, Item b) {
  nullCheck(a);
  nullCheck(b);
  if( ((node *)a)->cost > ((node *)b)->cost) return 0;
  else return 1;
}

short int getX(Item a) {
  return ((node *)a)->x;
}

short int getY(Item a) {
  return ((node *)a)->y;
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
