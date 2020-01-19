#include <stdio.h>
#include <stdlib.h>

#include "storage_engine.h"
#include "lock_manager/lock_manager.h"
#include "../log.h"
#include "page_manager/page_manager.h"
#include "btree/btree.h"

static engine* storage_engine;

void engine_start(char* path) {
    log_info("Starting storage engine with file backing `%s`\n", path);

    storage_engine = malloc(sizeof(engine));

    storage_engine->fd = -1;
    storage_engine->page_counter = 0;

    page_manager_init(storage_engine, path);

    lock_manager_init();
    storage_engine->btree = btree_malloc();
    lock_manager_release(storage_engine->btree->pid);
}

// reset engine. For testing purposes
void engine_reset() {
    btree_free(storage_engine->btree);
    storage_engine->page_counter = 0;

    page_manager_reset();

    lock_manager_stop();
    lock_manager_init();

    storage_engine->btree = btree_malloc();
    lock_manager_release(storage_engine->btree->pid);
}

void engine_stop() {
    btree_free(storage_engine->btree);

    lock_manager_stop();

    page_manager_stop();

    log_info("Storage engine stopped\n");
}

void engine_insert(long key, long value) {
    page_id root_pid = storage_engine->btree->pid;
    lock_manager_acquire(root_pid);

    storage_engine->btree = btree_insert(storage_engine->btree, key, value);

    lock_manager_release(root_pid);
}

void engine_delete(long key) {
    page_id root_pid = storage_engine->btree->pid;
    lock_manager_acquire(root_pid);

    storage_engine->btree = btree_delete(storage_engine->btree, key);

    lock_manager_release(root_pid);
}

long engine_get(long key) {
    lock_manager_acquire(storage_engine->btree->pid);

    long out = btree_get(storage_engine->btree, key);

    lock_manager_release(storage_engine->btree->pid);

    return out;
}

void engine_dump() {
    printf("Dumping storage engine\n");

    lock_manager_acquire(storage_engine->btree->pid);

    btree_print(storage_engine->btree);

    lock_manager_release(storage_engine->btree->pid);
}

long engine_size() {
    lock_manager_acquire(storage_engine->btree->pid);

    long out = btree_size(storage_engine->btree);

    lock_manager_release(storage_engine->btree->pid);

    return out;
}

long* engine_keys() {
    lock_manager_acquire(storage_engine->btree->pid);

    long* out = btree_keys(storage_engine->btree);

    lock_manager_release(storage_engine->btree->pid);

    return out;
}
