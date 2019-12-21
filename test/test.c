#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/engine/btree/btree.h"

#define REPEAT 3

bool includes(int data, int* arr, int size) {
    for (int i = 0; i < size; i += 1) {
        if (data == arr[i]) {
            return true;
        }
    }

    return false;
}

int test_btree_random_no_updates(int inserts) {
    btree* bt = btree_malloc();

    int* keys = malloc(inserts * sizeof(int));
    int* data = malloc(inserts * sizeof(int));
    for (int i = 0; i < inserts; i += 1) {
        int val;
        do {
            val = rand();
        } while (includes(val, keys, inserts));
        keys[i] = val;

        data[i] = rand();
        

        bt = btree_insert(bt, keys[i], data[i]);
    }

    for (int i = 0; i < inserts; i += 1) {
        if (btree_get(bt, keys[i]) != data[i]) {
            btree_print(bt);

            printf("Expected key: %d, value: %d\n", keys[i], data[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    btree_free(bt);

    return 0;
}

int main(int argc, char* argv[]) {
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random_no_updates(10);
        test_btree_random_no_updates(100);
        test_btree_random_no_updates(1000);
        test_btree_random_no_updates(10000);
    }
    
    return 0;
}