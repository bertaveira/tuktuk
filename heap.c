#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "funcs.h"

static Item *queue;
static int Qsize;

void heapInit(int size) {
  queue = (Item *)malloc(sizeof(Item)*size);
  for (i = 0; i<size; i++)
    queue[i]= NULL;
  Qsize = 0;
}

int heapEmpty() {
  if( queue[0] == NULL) return 1;
  else return 0;
}


//heapinit chamado ocm numero arbitrario!!!
void heapInsert(Item it, short int **mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)) {
  if(heapEmpty == 1)
    heapInit(5000);
  queue[Qsize] = it;
  mtx[gety(it)][getx(it)] = Qsize;
  qsize++;
  Fixup(Qsize, mtx, comp, gety, getx);
}



//mtx fica sempre a -1 (fazer lista de saida simplifica)
Item heapGetMax(short int ** mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)) {
  Item aux;
  aux = queue[0];
  Qsize--;
  queue[0] = queue[Qsize];
  Fixdown(0, mtx, comp, gety, getx);
  mtx[gety(aux)][gety(aux)] = -1;


  return aux;
}


void Fixdown(int pos, short int ** mtx, int (*comp)(Item, Item), short int (*gety)(Item), short int (*getx)(Item)){
  Item *aux;
  int i = (pos+1)*2;
  short int j = 0, y, x, z, w;
  if(pos == 0){
    return;
  }
  if(comp(queue[i],queue[i-1) >= 0){
    if(comp(queue[i],queue[pos) >= 0){
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
      Fixdown(i, mtx, comp, change);
      return;
    }
  }else if(comp(queue[i-1],queue[pos) >= 0){
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
    Fixdown(i-1, mtx, comp, change);
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
  if(comp(queue[pos],queue[i) >= 0){
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
    Fixup(i, mtx, comp, change);
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
