// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "page_manager.h"
#include "linked_list.h"

static engine* storage_engine;
static list* freelist;
static page_node* cache = NULL;
static int page_list_size = 0;

// initialize datafile
void page_manager_init(engine* e, char* path) {
    assert(e->fd == -1);

    e->fd = open(path, O_RDWR | O_CREAT);
    assert(e->fd != -1);

    long off = lseek(e->fd, 0, SEEK_SET);
    assert(off == 0);

    storage_engine = e;
}

void page_manager_reset() {
    cons_free(freelist);
    freelist = NULL;

    int rv = ftruncate(storage_engine->fd, 0);
    assert(rv != -1);

    long off = lseek(storage_engine->fd, 0, SEEK_SET);
    assert(off == 0);
}

// flush all pages to disk
void page_manager_stop() {
    int rv = close(storage_engine->fd);
    assert(rv != -1);

    cons_free(freelist);
}

page_id malloc_page() {
    page_id pid = storage_engine->page_counter;
    if (freelist != NULL) { // assign pid to be one of the free slots
        pid = freelist->car;
        freelist = freelist->cdr;
    } else {
        storage_engine->page_counter += 1;
    }

    page_node* page = malloc(PAGE_SIZE);
    memset(page, 0, PAGE_SIZE);
    flush_page(pid, page);

    // add the page to the cache if there's space
    // TODO: use a real algorithm for this, not Jake's super inefficient caching TM
    if (page_list_size <= MAX_PAGE_LIST_SIZE) {
        page->pid = pid;
        page->next = cache;

        cache = page;
        page_list_size += 1;
    } else {
        free(page);
    }

    return pid;
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    // TODO: check for page in cache

    long loc = pid * PAGE_SIZE;

    long off = lseek(storage_engine->fd, loc, SEEK_SET);
    assert(off == loc); // ensure file offset is correct

    void* page = malloc(PAGE_SIZE);

    ssize_t size = read(storage_engine->fd, page, PAGE_SIZE);
    assert(size == PAGE_SIZE);

    return page;
}

void flush_page(page_id pid, void* page) {
    // TODO: add page to cache

    long loc = pid * PAGE_SIZE;

    long off = lseek(storage_engine->fd, loc, SEEK_SET);
    assert(off == loc);

    int rv = write(storage_engine->fd, page, PAGE_SIZE);
    assert(rv != -1);
}

void free_page(page_id pid) {
    // add page_id to freelist so new mallocs can overwrite memory
    freelist = cons(pid, freelist);

    // delete the page from the cache
    page_node* prev_page = NULL;
    page_node* on_page = cache;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            if (prev_page == NULL) {
                page_node* tmp = cache;
                cache = cache->next;
                free(tmp);
                
                return;
            }

            prev_page->next = on_page->next;
            free(on_page);

            return;
        }

        prev_page = on_page;
        on_page = on_page->next;
    }
}
