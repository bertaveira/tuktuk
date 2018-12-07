#ifndef _HEAP_H_
#define _HEAP_H_

#include "defs.h"

void heapInit(int);
int heapEmpty();
void heapInsert(Item, bool **, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
Item heapGetMax(int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
void Fixdown(int, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
void Fixup(int, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
Item getItem(int);
void freeHeap();

#endif
