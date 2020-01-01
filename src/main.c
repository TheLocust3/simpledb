#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(1, 10);
    engine_insert(2, 10);
    engine_insert(3, 10);
    engine_insert(4, 10);
    engine_insert(5, 10);
    engine_insert(6, 10);
    
    engine_dump();

    engine_stop();

    return 0;
}
