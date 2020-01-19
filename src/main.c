#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(12, 64);
    engine_insert(74, 63);
    engine_insert(19, 37);
    engine_insert(94, 22);
    engine_insert(1, 74);
    engine_insert(66, 70);
    engine_insert(93, 37);
    engine_insert(88, 41);
    engine_insert(59, 98);
    engine_insert(13, 48);

    engine_delete(12);
    engine_delete(74);
    engine_delete(19);
    engine_delete(94);
    engine_delete(1);

    engine_dump();

    engine_stop();

    return 0;
}
