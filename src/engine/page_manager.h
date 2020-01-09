#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#include "btree/btree.h"

#define MAX_PAGE_LIST_SIZE 10

static const size_t PAGE_SIZE = sizeof(btree);

#include "storage_engine.h"

typedef long page_id;

void page_manager_init(engine* e, char* path);
void page_manager_reset();
void page_manager_stop();

page_id malloc_page();
void* get_page(page_id pid);
void flush_page(page_id pid, void* page);
void free_page(page_id pid);

#endif
