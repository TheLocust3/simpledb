#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"
#include "engine/page_manager.h"

int main(int argc, char* argv[]) {
    page_manager_init("test.dat");

    btree* bt = btree_malloc();
    
    btree_print(bt);

    btree_free(bt);

    page_manager_stop();

    return 0;
}
