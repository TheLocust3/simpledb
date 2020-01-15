#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(87, 79);
    engine_insert(71, 9);
    engine_insert(17, 20);
    engine_insert(24, 16);
    engine_insert(92, 75);
    engine_insert(86, 85);
    engine_insert(83, 25);
    engine_insert(42, 0);

    engine_insert(79, 11);

    engine_dump();

    engine_stop();

    return 0;
}
