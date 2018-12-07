#ifndef _HEAP_H_
#define _HEAP_H_

#include "defs.h"

void heapInit(int);
int heapEmpty();
void heapInsert(Item, int (*)(Item, Item));
Item heapGetMax(int (*)(Item, Item));
void Fixdown(int, int (*)(Item, Item));
void Fixup(int, int (*)(Item, Item));
Item getItem(int);
void freeHeap();

#endif
