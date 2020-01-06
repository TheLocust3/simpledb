#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(92, 27);
    engine_insert(81, 27);
    engine_insert(14, 53);
    engine_insert(71, 82);
    engine_insert(87, 0);
    engine_insert(66, 64);
    engine_insert(92, 27);
    engine_insert(51, 58);
    engine_insert(89, 2);
    engine_insert(22, 91);

    engine_dump();

    engine_delete(92);
    /*engine_delete(81);
    engine_delete(14);
    engine_delete(71);
    engine_delete(87);
    engine_delete(66);
    engine_delete(92);
    engine_delete(51);
    engine_delete(89);
    engine_delete(22);*/
    
    engine_dump();

    engine_stop();

    return 0;
}
