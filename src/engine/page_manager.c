// page manager
// manages in-memory page cache and persisting pages to disk transparently

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include "page_manager.h"

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
    page_id pid = storage_engine->page_counter;

    int rv = lseek(storage_engine->fd, pid * PAGE_SIZE, SEEK_SET);
    void* page = malloc(PAGE_SIZE);
    flush_page(pid, page);

    storage_engine->page_counter += 1;

    free(page);

    return pid;
}

// given page_id, check if we have a cached page otherwise convert the id into a location on disk
void* get_page(page_id pid) {
    int rv = lseek(storage_engine->fd, pid * PAGE_SIZE, SEEK_SET);
    assert(rv != -1);

    void* page = malloc(PAGE_SIZE);
    ssize_t size = read(storage_engine->fd, page, PAGE_SIZE);
    assert(size == PAGE_SIZE);

    return page;
}

void flush_page(page_id pid, void* page) {
    int rv = lseek(storage_engine->fd, pid * PAGE_SIZE, SEEK_SET);
    assert(rv != -1);

    rv = write(storage_engine->fd, page, PAGE_SIZE);
    assert(rv != -1);
}

void free_page(page_id pid) {
    // remove page from the cache, free page in memory, delete page on disk
    // TODO
}
