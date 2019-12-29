#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#define PAGE_SIZE 4096

typedef int page_id;

void page_manager_init(char* path);

page_id malloc_page();
void* get_page(page_id pid);
void free_page(page_id pid);

#endif
