#ifndef LOCK_LIST_H
#define LOCK_LIST_H

#include <pthread.h>

#define LOCK_LIST_SIZE_INIT 100
#define LOCK_LIST_GROWTH_FACTOR 10

typedef struct lock_list {
    pthread_mutex_t* locks;
    long elements;
    long size;
} lock_list;

lock_list* lock_list_malloc();
void lock_list_free(lock_list* list);
pthread_mutex_t lock_list_get(lock_list* list, long pid);
lock_list* lock_list_add(lock_list* list);

#endif
