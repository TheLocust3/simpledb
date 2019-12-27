#include <stdio.h>
#include <stdlib.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    btree* bt = btree_malloc();

    btree_print(bt);

    btree_free(bt);

    return 0;
}
