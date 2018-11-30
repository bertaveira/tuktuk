#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "funcs.h"

static Item *queue;
static int Qsize;

void heapInit(int size) {
  int i;
  queue = (Item *)malloc(sizeof(Item)*size);
  for (i = 0; i<size; i++)
    queue[i]= NULL;
  Qsize = 0;
}

int heapEmpty() {
  if( Qsize == 0) return 1;
  else return 0;
}


//heapinit chamado ocm numero arbitrario!!!
void heapInsert(Item it, short int **mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)) {
  if(heapEmpty() == 1)
    heapInit(5000); // ALTERAR ISTO
  queue[Qsize] = it;
  mtx[gety(it)][getx(it)] = Qsize;
  Fixup(Qsize, mtx, comp, gety, getx);
  Qsize++;
}



//mtx fica sempre a -1 (fazer lista de saida simplifica)
Item heapGetMax(short int ** mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)) {
  Item aux;
  if(Qsize == 0)
    return NULL;
  if(Qsize == 1){
    Qsize--;
    return queue[Qsize];
  }
  aux = queue[0];
  Qsize--;
  queue[0] = queue[Qsize];
  mtx[gety(queue[Qsize])][getx(queue[Qsize])] = 0;
  Fixdown(0, mtx, comp, gety, getx);
  mtx[gety(aux)][getx(aux)] = -1;


  return aux;
}


void Fixdown(int pos, short int ** mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)){
  Item *aux;
  int i = (pos+1)*2;
  short int j = 0, y, x, z, w;
  if(i > Qsize || i-1 > Qsize){
    return;
  }
  if(comp(queue[i],queue[i-1]) == 1){
    if(comp(queue[i],queue[pos]) == 1){
      y = gety(queue[pos]);
      x = getx(queue[pos]);
      z = gety(queue[i]);
      w = getx(queue[i]);
      j = mtx[y][x];
      mtx[y][x] = mtx[z][w];
      mtx[z][w] = j;

      aux = queue[pos];
      queue[pos] = queue[i];
      queue[i] = aux;
      Fixdown(i, mtx, comp, gety, getx);
      return;
    }
  }else if(comp(queue[i-1],queue[pos]) == 1){
    y = gety(queue[pos]);
    x = getx(queue[pos]);
    z = gety(queue[i-1]);
    w = getx(queue[i-1]);
    j = mtx[y][x];
    mtx[y][x] = mtx[z][w];
    mtx[z][w] = j;

    aux = queue[pos];
    queue[pos] = queue[i-1];
    queue[i-1] = aux;
    Fixdown(i-1, mtx, comp, gety, getx);
    return;
  }
  return;
}




void Fixup(int pos, short int ** mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)){
  Item *aux;
  int i = (pos-1)/2;
  short int j = 0, y, x, z, w;
  if(pos == 0){
    return;
  }
  if(comp(queue[pos],queue[i]) == 1){
    y = gety(queue[pos]);
    x = getx(queue[pos]);
    z = gety(queue[i]);
    w = getx(queue[i]);
    j = mtx[y][x];
    mtx[y][x] = mtx[z][w];
    mtx[z][w] = j;

    aux = queue[pos];
    queue[pos] = queue[i];
    queue[i] = aux;
    Fixup(i, mtx, comp, gety, getx);
    return;
  }
  return;
}


Item getItem(int x){
  if(x<Qsize){
    return queue[x];
  }
  return NULL;
}

void freeHeap() {
  int i;
  for( i = 0; i<Qsize; i++)
    free(queue[i]);
  free(queue);
  queue = NULL;
}
