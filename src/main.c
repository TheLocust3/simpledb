#include <stdio.h>
#include <stdlib.h>

#include "database/database.h"
#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    database_initialize("test.db");

    query_request write;
    write.op = QUERY_WRITE;

    query_response res;

    write.key = 94;
    write.val = 59;
    res = database_query(write);

    write.key = 44;
    write.val = 28;
    res = database_query(write);

    write.key = 42;
    write.val = 8;
    res = database_query(write);

    write.key = 24;
    write.val = 53;
    res = database_query(write);

    write.key = 7;
    write.val = 38;
    res = database_query(write);

    write.key = 52;
    write.val = 57;
    res = database_query(write);

    write.key = 82;
    write.val = 35;
    res = database_query(write);

    write.key = 33;
    write.val = 94;
    res = database_query(write);

    write.key = 61;
    write.val = 30;
    res = database_query(write);

    write.key = 14;
    write.val = 24;
    res = database_query(write);

    engine_dump();

    database_stop();

    return 0;
}
