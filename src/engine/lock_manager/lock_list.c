#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lock_list.h"

lock_list* lock_list_new(long size) {
    lock_list* list = malloc(sizeof(lock_list));
    list->elements = 0;
    list->size = size;
    list->locks = malloc(list->size * sizeof(pthread_mutex_t));

    return list;
}

lock_list* lock_list_malloc() {
    return lock_list_new(LOCK_LIST_SIZE_INIT);
}

void lock_list_free(lock_list* list) {
    for (int i = 0; i < list->elements; i += 1) {
        pthread_mutex_destroy(&list->locks[i]);
    }

    free(list->locks);
    free(list);
}

pthread_mutex_t* lock_list_get(lock_list* list, long pid) {
    assert(pid >= 0 && pid < list->elements);

    return &(list->locks[pid]);
}

lock_list* lock_list_expand(lock_list* list) {
    lock_list* new_list = lock_list_new(list->size * LOCK_LIST_GROWTH_FACTOR);

    for (int i = 0; i < list->size; i += 1) {
        new_list->locks[i] = list->locks[i];
        new_list->elements += 1;
    }

    free(list->locks);
    free(list);

    return new_list;
}

lock_list* lock_list_add(lock_list* list) {
    if (list->elements >= list->size) {
        list = lock_list_expand(list);
    }

    int rv = pthread_mutex_init(&list->locks[list->elements], NULL);
    assert(rv == 0);

    list->elements += 1;

    return list;
}

void lock_list_reset(lock_list* list, long pid) {
    assert(pid >= 0 && pid < list->elements);

    int rv = pthread_mutex_init(&list->locks[pid], NULL);
    assert(rv == 0);
}
