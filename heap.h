#ifndef _HEAP_H_
#define _HEAP_H_

#include "defs.h"

void heapInit(int); /* inicializa fila com prioridade */
/* com número máximo de items */
BOOL heapEmpty(); /* testa fila vazia */
void heapInsert(Item); /* insere item */
Item heapDelmax(); /* elimina item de maior prioridade */

#endif
