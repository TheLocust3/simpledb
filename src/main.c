#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"
#include "engine/page_manager.h"

int main(int argc, char* argv[]) {
    page_manager_init("test.dat");

    btree* bt = btree_malloc();
    bt = btree_insert(bt, 1, 10);
    bt = btree_insert(bt, 2, 10);
    bt = btree_insert(bt, 3, 10);
    bt = btree_insert(bt, 4, 10);
    bt = btree_insert(bt, 5, 10);
    bt = btree_insert(bt, 6, 10);
    
    btree_print(bt);

    btree_free(bt);

    page_manager_stop();

    return 0;
}
