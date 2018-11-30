#ifndef _HEAP_H_
#define _HEAP_H_

#include "defs.h"

void heapInit(int);
int heapEmpty();
void heapInsert(Item, short int **, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
Item heapGetMax(short int **, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
void Fixdown(int, short int **, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
void Fixup(int, short int **, int (*)(Item, Item), short int (*)(Item), short int (*)(Item));
Item getItem(int);

#endif
