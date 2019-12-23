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

    btree_print(bt);

    bt = btree_delete(bt, 9);

    btree_print(bt);

    btree_free(bt);

    return 0;
}
