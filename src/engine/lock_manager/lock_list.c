#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lock_list.h"

lock_list* lock_list_malloc() {
    lock_list* list = malloc(sizeof(lock_list));
    list->elements = 0;
    list->size = LOCK_LIST_SIZE_INIT;
    list->locks = malloc(list->size * sizeof(pthread_mutex_t));

    return list;
}

void lock_list_free(lock_list* list) {
    for (int i = 0; i < list->elements; i += 1) {
        pthread_mutex_destroy(&list->locks[i]);
    }

    free(list->locks);
    free(list);
}

pthread_mutex_t lock_list_get(lock_list* list, long pid) {
    assert(pid > 0 && pid < list->size);

    return list->locks[pid];
}

void lock_list_add(lock_list* list) {
    if (list->elements >= list->size) {
        printf("Implement lock list expanding");
        abort();
    }

    int rv = pthread_mutex_init(&list->locks[list->elements], NULL);
    assert(rv == 0);

    list->elements += 1;
}
