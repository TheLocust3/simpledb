#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "helpers.h"
#include "../src/engine/btree/btree.h"

#define REPEAT 3

void test_btree_delete(btree* bt, long* keys, int inserts) {
    for (int i = 0; i < inserts; i += 1) {
        bt = btree_delete(bt, keys[i]);
        
        if (btree_get(bt, keys[i]) != -1) {
            btree_print(bt);

            printf("Failed to delete key: %ld\n", keys[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));

            abort();
        }
    }
}

void test_btree_size(btree* bt, long expected_size) {
    if (btree_size(bt) != expected_size) {
        btree_print(bt);

        printf("Expected size of btree to be %ld\n", expected_size);
        printf("Found size of %ld\n", btree_size(bt));

        abort();
    }
}

int test_btree_random_no_updates(int inserts) {
    int max_key_val = inserts * 10;

    btree* bt = btree_malloc();

    long* keys = malloc(inserts * sizeof(long));
    long* data = malloc(inserts * sizeof(long));
    for (int i = 0; i < inserts; i += 1) {
        long val;
        do {
            val = nat_rand(max_key_val);
        } while (includes(val, keys, i));
        keys[i] = val;

        data[i] = nat_rand(max_key_val);
        

        bt = btree_insert(bt, keys[i], data[i]);
    }

    test_btree_size(bt, inserts);

    for (int i = 0; i < inserts; i += 1) {
        if (btree_get(bt, keys[i]) != data[i]) {
            btree_print(bt);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(bt, keys, inserts);
    test_btree_size(bt, 0);

    btree_free(bt);

    return 0;
}

int test_btree_random(int inserts) {
    int max_key_val = inserts * 10;
    
    btree* bt = btree_malloc();

    long* keys = malloc(inserts * sizeof(long));
    long* data = malloc(inserts * sizeof(long));
    for (int i = 0; i < inserts; i += 1) {
        keys[i] = nat_rand(max_key_val);

        int index = index_of(keys[i], keys, i);
        if (index != -1) {
            data[i] = data[index];
        } else {
            data[i] = nat_rand(max_key_val);
        }

        bt = btree_insert(bt, keys[i], data[i]);
    }

    for (int i = 0; i < inserts; i += 1) {
        if (btree_get(bt, keys[i]) != data[i]) {
            btree_print(bt);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(bt, keys, inserts);
    test_btree_size(bt, 0);

    btree_free(bt);

    return 0;
}

int main(int argc, char* argv[]) {
    time_t t;
    srand((unsigned) time(&t));

    printf("Running btree_random_no_updates\n");
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random_no_updates(10);
        test_btree_random_no_updates(100);
        test_btree_random_no_updates(1000);
        test_btree_random_no_updates(10000);
    }

    printf("btree_random_no_updates passed!\n\n");

    printf("Running btree_random\n");
    
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random(10);
        test_btree_random(100);
        test_btree_random(1000);
        test_btree_random(10000);
    }

    printf("btree_random passed!\n\n");
    
    return 0;
}