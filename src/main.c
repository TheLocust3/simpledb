#include <stdio.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    printf("Hello World!\n");

    btree* test = btree_malloc();

    printf("Start size: %ld\n", btree_size(test));
    btree_print(test);

    test = btree_insert(test, 7, 10);
    test = btree_insert(test, 6, 10);
    test = btree_insert(test, 4, 12);
    test = btree_insert(test, 3, 12);
    test = btree_insert(test, 1, 12);

    printf("End size: %ld\n", btree_size(test));
    btree_print(test);

    btree_free(test);
    
    return 0;
}