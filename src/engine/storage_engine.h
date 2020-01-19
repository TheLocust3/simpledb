#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

#include "btree/btree.h"

typedef struct engine {
    btree* btree;
    int fd;
    long page_counter;
} engine;

engine* engine_start(char* path);
void engine_reset();
void engine_stop();

void engine_insert(long key, long value);
void engine_delete(long key);
long engine_get(long key);

void engine_dump();
long engine_size();
long* engine_keys();

#endif
