#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list {
    long car;
    struct list* cdr;
} list;

list* cons(long car, list* cdr);
void cons_free(list* head);

#endif