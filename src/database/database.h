#ifndef DATABASE_H
#define DATABASE_H

#include "query.h"
#include "../engine/storage_engine.h"

typedef struct database {
    engine* sengine;
} database;

void database_initialize(char* path);
void database_start(char* path);
void database_stop();

query_response database_query(query_request q);

#endif
