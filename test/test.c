#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/engine/btree/btree.h"

#define INSERTS 30
#define KEY_MAX 1000
#define DATA_MAX 1000

bool includes(int data, int* arr, int size) {
    for (int i = 0; i < size; i += 1) {
        if (data == arr[i]) {
            return true;
        }
    }

    return false;
}

int test_btree_random() {
    btree* bt = btree_malloc();

    int* keys = malloc(INSERTS * sizeof(int));
    int* data = malloc(INSERTS * sizeof(int));
    for (int i = 0; i < INSERTS; i += 1) {
        int val;
        do {
            val = rand() % KEY_MAX;
        } while (includes(val, keys, INSERTS));
        keys[i] = val;

        data[i] = rand() % DATA_MAX;
        

        bt = btree_insert(bt, keys[i], data[i]);
    }

    for (int i = 0; i < INSERTS; i += 1) {
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

    test_btree_random();
    
    return 0;
}