// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <assert.h>

#include "page_manager.h"

static long page_counter = 0;
static page* cache_head; // linked list of all cached pages

void page_manager_init(char* path) {
    // TODO: actually persist to a file
}

void page_manager_stop() {
    // TODO: flush all pages to disk
}

page_id malloc_page() {
    page* page = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    page->pid = page_counter;
    page->next = cache_head;

    cache_head = page; // cache the page, it's assumed that the client will be using it in a moment

    page_counter += 1;

    return page->pid;
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    page* on_page = cache_head;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            return (void*) (((char*) on_page) + sizeof(page_id)); // shift returned mem past id, so client doesn't overwrite vital information
        }

        on_page = on_page->next;
    }

    printf("Implement getting page from disk\n");
    abort();
}

void free_page(page_id pid) {
    // don't immediately free the page and remove it from the cache
    // update cache and flush page to disk
}
