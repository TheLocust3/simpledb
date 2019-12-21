#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    btree* bt = btree_malloc();

    bt = btree_insert(bt, 1, 10);

    btree_print(bt);

    bt = btree_delete(bt, 1);

    btree_print(bt);

    btree_free(bt);

    return 0;
}
