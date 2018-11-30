#ifndef _DEFS_H_
#define _DEFS_H_

typedef void *Item;

typedef struct _list {
  Item item;
  list *next;
} list;

#endif
