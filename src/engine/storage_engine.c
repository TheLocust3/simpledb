#include <stdio.h>
#include <stdlib.h>

#include "storage_engine.h"
#include "../log.h"
#include "page_manager.h"
#include "btree/btree.h"

static engine* storage_engine;

void engine_start(char* path) {
    log_info("Starting storage engine with file backing `%s`\n", path);

    storage_engine = malloc(sizeof(engine));

    storage_engine->fd = -1;
    storage_engine->page_counter = 0;

    page_manager_init(storage_engine, path);

    storage_engine->btree = btree_malloc();
}

// reset engine. For testing purposes
void engine_reset() {
    storage_engine->page_counter = 0;
    btree_free(storage_engine->btree);

    page_manager_reset();
    storage_engine->btree = btree_malloc();
}

void engine_stop() {
    log_info("Stopping storage engine\n");

    btree_free(storage_engine->btree);
    page_manager_stop();
}

void engine_insert(long key, long value) {
    storage_engine->btree = btree_insert(storage_engine->btree, key, value);
}

void engine_delete(long key) {
    storage_engine->btree = btree_delete(storage_engine->btree, key);
}

long engine_get(long key) {
    return btree_get(storage_engine->btree, key);
}

void engine_dump() {
    printf("Dumping storage engine\n");

    btree_print(storage_engine->btree);
}

long engine_size() {
    return btree_size(storage_engine->btree);
}

long* engine_keys() {
    return btree_keys(storage_engine->btree);
}
