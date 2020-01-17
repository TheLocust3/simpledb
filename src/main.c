#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(54, 20);
    engine_insert(28, 54);
    engine_insert(80, 5);
    engine_insert(79, 63);
    engine_insert(57, 1);
    engine_insert(16, 11);
    engine_insert(40, 64);
    engine_insert(6, 37);
    engine_insert(84, 35);
    engine_insert(34, 87);

    engine_delete(54);

    engine_dump();

    engine_stop();

    return 0;
}
