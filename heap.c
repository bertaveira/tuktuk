#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "funcs.h"

static Item *queue;
static int Qsize;
static int alocSize;



//in: size -- size of heap to init
void heapInit(int size) {
  int i;
  alocSize = size;
  queue = (Item *)malloc(sizeof(Item)*size);
  for (i = 0; i<size; i++)
    queue[i]= NULL;
  Qsize = 0;
}


int heapEmpty() {
  if( Qsize == 0) return 1;
  else return 0;
}


void heapInsert(Item it, int (*comp)(Item, Item)) {
  queue[Qsize] = it;
  Fixup(Qsize, comp);
  Qsize++;
}




Item heapGetMax(int (*comp)(Item, Item)) {
  Item aux;
  if(Qsize == 0)
    return NULL;
  aux = queue[0];
  Qsize--;
  queue[0] = queue[Qsize];
  Fixdown(0, comp);
  return aux;
}


void Fixdown(int pos, int (*comp)(Item, Item)){
  Item *aux;
  int i = (pos+1)*2;
  if(i > Qsize || i-1 > Qsize){
    return;
  }
  if(comp(queue[i],queue[i-1]) == 1){
    if(comp(queue[i],queue[pos]) == 1){
      aux = queue[pos];
      queue[pos] = queue[i];
      queue[i] = aux;
      Fixdown(i, comp);
      return;
    }
  }else if(comp(queue[i-1],queue[pos]) == 1){
    aux = queue[pos];
    queue[pos] = queue[i-1];
    queue[i-1] = aux;
    Fixdown(i-1, comp);
    return;
  }
  return;
}


void Fixup(int pos, int (*comp)(Item, Item)){
  Item *aux;
  int i = (pos-1)/2;
  if(pos == 0){
    return;
  }
  if(comp(queue[pos],queue[i]) == 1){
    aux = queue[pos];
    queue[pos] = queue[i];
    queue[i] = aux;
    Fixup(i, comp);
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

void freeHeap(){
  int i;
  for(i = 0; i<Qsize; i++)
    free(queue[i]);
  free(queue);
  queue = NULL;
  Qsize = 0;
}
