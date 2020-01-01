#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "helpers.h"
#include "../src/engine/btree/btree.h"

#define REPEAT 1

void error_dump(btree* bt, long* keys, long* data, int size) {
    printf("ERROR DUMPING STATE\n");

    btree_print(bt);

    printf("INSERT ORDER");

    for (int i = 0; i < size; i += 1) {
        printf("bt = btree_insert(bt, %ld, %ld);\n", keys[i], data[i]);
    }
}

void test_btree_delete(btree* bt, long* keys, long* data, int inserts) {
    for (int i = 0; i < inserts; i += 1) {
        bt = btree_delete(bt, keys[i]);
        
        if (btree_get(bt, keys[i]) != -1) {
            error_dump(bt, keys, data, inserts);

            printf("Failed to delete key: %ld\n", keys[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));

            abort();
        }
    }
}

void test_btree_size(btree* bt, long* keys, long* data, long expected_size) {
    if (btree_size(bt) != expected_size) {
        error_dump(bt, keys, data, expected_size);

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

    test_btree_size(bt, keys, data, inserts);

    for (int i = 0; i < inserts; i += 1) {
        if (btree_get(bt, keys[i]) != data[i]) {
            error_dump(bt, keys, data, inserts);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(bt, keys, data, inserts);
    test_btree_size(bt, keys, data, 0);

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
            error_dump(bt, keys, data, inserts);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", btree_get(bt, keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(bt, keys, data, inserts);
    test_btree_size(bt, keys, data, 0);

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
        // test_btree_random_no_updates(10000);
    }

    printf("btree_random_no_updates passed!\n\n");

    printf("Running btree_random\n");
    
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random(10);
        test_btree_random(100);
        test_btree_random(1000);
        // test_btree_random(10000);
    }

    printf("btree_random passed!\n\n");
    
    return 0;
}