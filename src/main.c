#include <stdio.h>
#include <stdlib.h>

#include "engine/storage_engine.h"

int main(int argc, char* argv[]) {
    engine_start("test.db");

    engine_insert(11, 40);
    engine_insert(59, 92);
    engine_insert(84, 37);
    engine_insert(40, 19);
    engine_insert(1, 64);
    engine_insert(13, 31);
    engine_insert(79, 34);
    engine_insert(63, 36);
    engine_insert(88, 5);
    engine_insert(82, 46);

    engine_delete(11);
    /*engine_delete(59);
    engine_delete(84);
    engine_delete(40);
    engine_delete(1);
    engine_delete(13);
    engine_delete(79);
    engine_delete(63);
    engine_delete(88);
    engine_delete(82);*/
    
    engine_dump();

    engine_stop();

    return 0;
}
