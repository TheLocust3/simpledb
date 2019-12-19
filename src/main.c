#include <stdio.h>

#include "engine/btree/btree.h"

int main(int argc, char* argv[]) {
    printf("Hello World!\n");

    btree* test = btree_malloc();

    test = btree_insert(test, 7, 10);
    test = btree_insert(test, 6, 10);
    test = btree_insert(test, 4, 12);
    test = btree_insert(test, 3, 12);
    test = btree_insert(test, 1, 12);
    test = btree_insert(test, 1, 11);

    test = btree_insert(test, 15, 20);
    test = btree_insert(test, 13, 19);
    test = btree_insert(test, 2, 19);
    test = btree_insert(test, 0, 19);
    test = btree_insert(test, 12, 19);

    test = btree_insert(test, 5, 420);
    test = btree_insert(test, 69, 420);
    test = btree_insert(test, 70, 420);
    test = btree_insert(test, 71, 420);
    test = btree_insert(test, 72, 420);
    test = btree_insert(test, 73, 420);
    test = btree_insert(test, 74, 420);
    test = btree_insert(test, 75, 420);
    test = btree_insert(test, 76, 420);
    test = btree_insert(test, 77, 420);

    printf("\nSize: %ld\n", btree_size(test));
    btree_print(test);

    btree_free(test);
    
    return 0;
}