#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "funcs.h"

static Item *queue;
static int Qsize

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

void heapInsert(Item it) {
  queue[size++] = it;
}

void heapDelmax() {
  int i = 0;
  while( queue[i] != NULL) {
    queue[i] = queue[i+1];
    i++;
  }
}


Item heapGetMax() {
  return (Item)queue[0];
}
