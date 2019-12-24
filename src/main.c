#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    btree* bt = btree_malloc();

    bt = btree_insert(bt, 1, 10);
    bt = btree_insert(bt, 2, 10);
    bt = btree_insert(bt, 3, 10);
    bt = btree_insert(bt, 4, 10);
    bt = btree_insert(bt, 5, 10);
    bt = btree_insert(bt, 6, 10);
    bt = btree_insert(bt, 7, 10);
    bt = btree_insert(bt, 8, 10);
    bt = btree_insert(bt, 9, 10);
    bt = btree_insert(bt, 10, 10);
    bt = btree_insert(bt, 11, 10);
    bt = btree_insert(bt, 12, 10);
    bt = btree_insert(bt, 13, 10);
    bt = btree_insert(bt, 14, 10);
    bt = btree_insert(bt, 15, 10);
    bt = btree_insert(bt, 16, 10);
    bt = btree_insert(bt, 17, 10);
    bt = btree_insert(bt, 18, 10);
    bt = btree_insert(bt, 19, 10);
    bt = btree_insert(bt, 20, 10);
    bt = btree_insert(bt, 21, 10);
    bt = btree_insert(bt, 22, 10);
    bt = btree_insert(bt, 23, 10);
    bt = btree_insert(bt, 24, 10);

    btree_print(bt);

    bt = btree_delete(bt, 1);
    bt = btree_delete(bt, 2);
    bt = btree_delete(bt, 3);
    bt = btree_delete(bt, 4);
    // bt = btree_delete(bt, 5);

    btree_print(bt);

    btree_free(bt);

    return 0;
}
