// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <assert.h>

#include "page_manager.h"

static long page_counter = 0;
static page* cache_head = NULL; // linked list of all cached pages

// initialize datafile
void page_manager_init(char* path) {

}

// flush all pages to disk
void page_manager_stop() {

}

page_id malloc_page() {
    page* pg = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    pg->pid = page_counter;
    pg->next = cache_head;

    cache_head = pg; // cache the new page

    page_counter += 1;

    return pg->pid;
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    page* on_page = cache_head;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            return (void*) (((char*) on_page) + sizeof(page)); // shift returned mem past page info, so client doesn't overwrite vital information
        }

        on_page = on_page->next;
    }

    // get page from disk
    // cache the page, clean up old pages in the cache

    printf("Implement getting page from disk\n");
    abort();
}

void free_page(page_id pid) {
    // flush page to disk, remove it from the cache
}
