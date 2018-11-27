#ifndef _HEAP_H_
#define _HEAP_H_

#include "defs.h"

void heapInit(int);
int heapEmpty();
void heapInsert(Item);
void heapDelmax();
Item heapGetMax();

#endif
