#ifndef PAGE_MANAGER_H
#define PAGE_MANAGER_H

#define PAGE_SIZE 4096

typedef long page_id;

typedef struct page {
    page_id pid;
    struct page* next;
} page;

void page_manager_init(char* path);
void page_manager_stop();

page_id malloc_page();
void* get_page(page_id pid);
void free_page(page_id pid);

#endif
