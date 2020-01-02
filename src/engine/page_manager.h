#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#define PAGE_SIZE 4096

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
