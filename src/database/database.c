#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "../engine/storage_engine.h"
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

query_response database_query_read(query_request q) {
    long val = engine_get(q.key);

    query_response res;
    res.op = q.op;
    res.code = RESPONSE_SUCCESS;
    res.val = val;

    return res;
}

query_response database_query_write(query_request q) {
    engine_insert(q.key, q.val);

    query_response res;
    res.op = q.op;
    res.code = RESPONSE_SUCCESS;
    res.val = -1;

    return res;
}

query_response database_query_remove(query_request q) {
    engine_delete(q.key);

    query_response res;
    res.op = q.op;
    res.code = RESPONSE_SUCCESS;
    res.val = -1;

    return res;
}

query_response database_query(query_request q) {
    query_print(q);

    if (q.op == QUERY_READ) {
        return database_query_read(q);
    } else if (q.op == QUERY_WRITE) {
        return database_query_write(q);
    } else if (q.op == QUERY_REMOVE) {
        return database_query_remove(q);
    } else {
        printf("Bad query operation %d received\n", q.op);
        abort();
    }
}
