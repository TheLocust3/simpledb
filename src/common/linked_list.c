#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void cons_free(list* head) {
    if (head == NULL) {
        return;
    }

    cons_free(head->cdr);
    free(head);
}

list* cons(long car, list* cdr) {
    list* head = malloc(sizeof(list));
    head->car = car;
    head->cdr = cdr;

    return head;
}