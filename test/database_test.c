#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "database_test.h"
#include "../src/database/database.h"
#include "../src/database/query.h"
#include "helpers.h"

void database_test() {
    printf("Running full database tests\n\n");

    database_initialize("test1.db");

    printf("\n");

    query_request write;
    write.op = QUERY_WRITE;
    write.key = 0;
    write.val = 10;

    query_request read;
    read.op = QUERY_READ;
    read.key = 0;

    query_request delete;
    delete.op = QUERY_REMOVE;
    delete.key = 0;

    query_response res = database_query(write);
    assert(res.op == QUERY_WRITE);
    assert(res.code == RESPONSE_SUCCESS);

    res = database_query(read);
    assert(res.op == QUERY_READ);
    assert(res.code == RESPONSE_SUCCESS);
    assert(res.val == 10);

    res = database_query(delete);
    assert(res.op == QUERY_REMOVE);
    assert(res.code == RESPONSE_SUCCESS);

    res = database_query(read);
    assert(res.op == QUERY_READ);
    assert(res.code == RESPONSE_SUCCESS);
    assert(res.val == -1);

    printf("\n");

    database_stop();

    printf("\nFull database tests passed\n");
}
