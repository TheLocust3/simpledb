#include <stdio.h>
#include <stdlib.h>

#include "breadcrumb_lock.h"
#include "../../log.h"
#include "lock_manager.h"
#include "lock_list.h"

breadcrumb_list* breadcrumb_lock_malloc() {
    return NULL;
}

void breadcrumb_lock_free(breadcrumb_list* list) {
    breadcrumb_list* tmp = list;
    while (tmp != NULL) {
        lock_manager_release(tmp->car);
    }

    cons_free(list);
}

breadcrumb_list* breadcrumb_lock_push(breadcrumb_list* list, long pid) {
    lock_manager_acquire(pid);

    return cons(pid, list);
}

breadcrumb_list* breadcrumb_lock_pop(breadcrumb_list* list) {
    long pid = list->car;
    lock_manager_release(pid);

    return list->cdr;
}
