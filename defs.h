#ifndef _DEFS_H_
#define _DEFS_H_

typedef void *Item;

typedef struct _list {
  Item item;
  struct _list *next;
} list;

typedef enum { false, true } bool;

#endif
