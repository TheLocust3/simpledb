// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "page_manager.h"
#include "../lock_manager/lock_manager.h"
#include "linked_list.h"
#include "../../log.h"

static engine* storage_engine;
static list* freelist;

// initialize datafile
void page_manager_init(engine* e, char* path) {
    log_debug("[PAGE_MANAGER]: Initializing\n");

    assert(e->fd == -1, "page_manager_init: e->fd == -1");

    e->fd = open(path, O_RDWR | O_CREAT);
    assert(e->fd != -1, "page_manager_init: e->fd != -1");

    long off = lseek(e->fd, 0, SEEK_SET);
    assert(off == 0, "page_manager_init: off == 0");

    storage_engine = e;
}

void page_manager_reset() {
    log_debug("[PAGE_MANAGER]: Reseting\n");

    cons_free(freelist);
    freelist = NULL;

    int rv = ftruncate(storage_engine->fd, 0);
    assert(rv != -1, "page_manager_reset: rv != -1");

    long off = lseek(storage_engine->fd, 0, SEEK_SET);
    assert(off == 0, "page_manager_reset: off == 0");
}

// flush all pages to disk
void page_manager_stop() {
    int rv = close(storage_engine->fd);
    assert(rv != -1, "page_manager_stop: rv != -1");

    cons_free(freelist);
    freelist = NULL;

    storage_engine = NULL;

    log_debug("[PAGE_MANAGER]: Stopped\n");
}

bool is_valid_page_id(page_id pid) {
    return pid == -1 || (pid >= 0 && pid <= storage_engine->page_counter);
}

page_id malloc_page() {
    lock_manager_acquire_special(FILE_LOCK);
    
    page_id pid = storage_engine->page_counter;
    if (freelist != NULL) { // assign pid to be one of the free slots
        pid = freelist->car;
        freelist = freelist->cdr;
    } else {
        storage_engine->page_counter += 1;
    }

    void* page = malloc(PAGE_SIZE);
    memset(page, 0, PAGE_SIZE);
    flush_page(pid, page);

    lock_manager_release_special(FILE_LOCK);

    return pid;
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    lock_manager_acquire_special(FILE_LOCK);

    long loc = pid * PAGE_SIZE;

    long off = lseek(storage_engine->fd, loc, SEEK_SET);
    assert(off == loc, "get_page: off == loc"); // ensure file offset is correct

    void* page = malloc(PAGE_SIZE);

    ssize_t size = read(storage_engine->fd, page, PAGE_SIZE);
    assert(size == PAGE_SIZE, "get_page: size == PAGE_SIZE");

    lock_manager_release_special(FILE_LOCK);

    return page;
}

void flush_page(page_id pid, void* page) {
    long loc = pid * PAGE_SIZE;

    long off = lseek(storage_engine->fd, loc, SEEK_SET);
    assert(off == loc, "flush_page: off == loc");

    int rv = write(storage_engine->fd, page, PAGE_SIZE);
    assert(rv != -1, "flush_page: rv != -1");
}

void free_page(page_id pid) {
    lock_manager_acquire_special(FILE_LOCK);

    // add page_id to freelist so new mallocs can overwrite memory
    freelist = cons(pid, freelist);

    lock_manager_release_special(FILE_LOCK);
}
