// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "page_manager.h"

static page* cache_head = NULL; // linked list of all cached pages
static engine* storage_engine;

// initialize datafile
void page_manager_init(engine* e, char* path) {
    assert(e->fd == -1);

    e->fd = open(path, O_RDWR | O_CREAT);
    assert(e->fd != -1);

    int rv = lseek(e->fd, 0, SEEK_SET);
    assert(rv != -1);

    storage_engine = e;
}

void page_manager_reset() {
    int rv = ftruncate(storage_engine->fd, 0);
    assert(rv != -1);

    rv = lseek(storage_engine->fd, 0, SEEK_SET);
    assert(rv != -1);
}

// flush all pages to disk
void page_manager_stop() {
    int rv = close(storage_engine->fd);
    assert(rv != -1);
}

page_id malloc_page() {
    int rv = lseek(storage_engine->fd, 0, SEEK_END);
    assert(rv != -1);

    page* pg = malloc(PAGE_SIZE);
    rv = write(storage_engine->fd, pg, PAGE_SIZE);
    assert(rv != -1);

    pg->pid = storage_engine->page_counter;
    pg->next = cache_head;

    cache_head = pg; // cache the new page

    storage_engine->page_counter += 1;

    return pg->pid;
}

page* get_page_raw(page_id pid) {
    int rv = lseek(storage_engine->fd, 0, SEEK_SET);
    assert(rv != -1);

    page* on_page = cache_head;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            return on_page;
        }

        on_page = on_page->next;
    }

    // get page from disk
    // cache the page, clean up old pages in the cache

    printf("Implement getting page from disk\n");
    abort();
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    page* pg = get_page_raw(pid);
    
    return (void*) (((char*) pg) + sizeof(page)); // shift returned mem past page info, so client doesn't overwrite vital information
}

void free_page(void* pg) {
    // remove page from the cache, free page in memory
}
