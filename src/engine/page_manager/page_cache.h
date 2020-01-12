#ifndef PAGE_CACHE_H
#define PAGE_CACHE_H

#include <stdbool.h>

#define MAX_PAGE_CACHE_SIZE 0

typedef struct page_node {
    long pid;
    struct page_node* next;
} page_node;

bool page_cache_add(long pid, void* mem);
void page_cache_remove(long pid);
void* page_cache_get(long pid);

#endif
