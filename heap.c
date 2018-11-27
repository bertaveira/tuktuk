#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "heap.h"
#include "funcs.h"

static Item *queue;

void heapInit(int size) {
  queue = (Item *)malloc(sizeof(Item)*size);
  for (i = 0; i<size; i++)
    queue[i]= NULL;
}
