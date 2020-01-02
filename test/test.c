#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "helpers.h"
#include "../src/engine/storage_engine.h"

#define REPEAT 1

void error_dump(long* keys, long* data, int size) {
    printf("\n\nFAILED... DUMPING STATE\n");

    engine_dump();

    printf("INSERT ORDER\n");

    for (int i = 0; i < size; i += 1) {
        printf("engine_insert(%ld, %ld);\n", keys[i], data[i]);
    }

    printf("\n\n");
}

void test_btree_delete(long* keys, long* data, int inserts) {
    for (int i = 0; i < inserts; i += 1) {
        engine_delete(keys[i]);
        
        if (engine_get(keys[i]) != -1) {
            error_dump(keys, data, inserts);

            printf("Failed to delete key: %ld\n", keys[i]);
            printf("Found value: %ld\n", engine_get(keys[i]));

            abort();
        }
    }
}

void test_btree_size(long* keys, long* data, long expected_size) {
    if (engine_size() != expected_size) {
        error_dump(keys, data, expected_size);

        printf("Expected size of btree to be %ld\n", expected_size);
        printf("Found size of %ld\n", engine_size());

        abort();
    }
}

int test_btree_random_no_updates(int inserts) {
    engine_reset();

    int max_key_val = inserts * 10;

    long* keys = malloc(inserts * sizeof(long));
    long* data = malloc(inserts * sizeof(long));
    for (int i = 0; i < inserts; i += 1) {
        long val;
        do {
            val = nat_rand(max_key_val);
        } while (includes(val, keys, i));
        keys[i] = val;

        data[i] = nat_rand(max_key_val);
        

        engine_insert(keys[i], data[i]);
    }

    test_btree_size(keys, data, inserts);

    for (int i = 0; i < inserts; i += 1) {
        if (engine_get(keys[i]) != data[i]) {
            error_dump(keys, data, inserts);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", engine_get(keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(keys, data, inserts);
    test_btree_size(keys, data, 0);

    return 0;
}

int test_btree_random(int inserts) {
    engine_reset();

    int max_key_val = inserts * 10;

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

        engine_insert(keys[i], data[i]);
    }

    for (int i = 0; i < inserts; i += 1) {
        if (engine_get(keys[i]) != data[i]) {
            error_dump(keys, data, inserts);

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", engine_get(keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }

    test_btree_delete(keys, data, inserts);
    test_btree_size(keys, data, 0);

    return 0;
}

int main(int argc, char* argv[]) {
    time_t t;
    srand((unsigned) time(&t));

    engine_start("test.db");

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

    engine_stop();
    
    return 0;
}