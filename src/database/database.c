#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "../log.h"

static database* d;

void database_initialize(char* path) {
    log_info("Initializing new database with file backing `%s`\n", path);

    // TODO: ensure file is truncated

    d = malloc(sizeof(database));
    d->sengine = engine_start(path);
}

void database_start(char* path) {
    log_info("Starting database with file backing `%s`\n", path);

    // TODO: ensure file exists

    d = malloc(sizeof(database));
    d->sengine = engine_start(path);
}

void database_stop() {
    log_info("Stopping database...\n");

    engine_stop();

    log_info("Database stopped\n");
}

query_response database_query(query_request q) {
    // print query

    // parse query
    
    // send query to storage engine

    query_response res;
    res.op = q.op;
    res.code = RESPONSE_SUCCESS;
    res.val = 0;

    return res;
}
