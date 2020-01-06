#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "helpers.h"
#include "../src/engine/storage_engine.h"

#define REPEAT 3

void error_dump() {
    printf("\n\nFAILED... DUMPING STATE\n");

    engine_dump();

    printf("\n\n");
}

void test_btree_size(long expected_size) {
    if (engine_size() != expected_size) {
        error_dump();

        printf("Expected size of btree to be %ld\n", expected_size);
        printf("Found size of %ld\n", engine_size());

        abort();
    }
}

void test_btree_gets(long* keys, long* data, long size) {
    test_btree_size(size);

    for (int i = 0; i < size; i += 1) {
        if (engine_get(keys[i]) != data[i]) {
            error_dump();

            printf("Expected key: %ld, value: %ld\n", keys[i], data[i]);
            printf("Found value: %ld\n", engine_get(keys[i]));
            printf("test_btree_random failed!\n");

            abort();
        }
    }
}

void test_btree_delete(long* keys, long* data, int inserts, bool fast) {
    for (int i = 0; i < inserts; i += 1) {
        engine_delete(keys[i]);
        
        if (engine_get(keys[i]) != -1) {
            error_dump();

            printf("Failed to delete key: %ld\n", keys[i]);
            printf("Found value: %ld\n", engine_get(keys[i]));

            abort();
        }

        if (!fast) {
            test_btree_gets(keys + i + 1, data + i + 1, inserts - i - 1); // ensure that we haven't lost any data
        }
    }
}

int test_btree_random_no_updates(int inserts, bool fast) {
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

    test_btree_gets(keys, data, inserts);

    test_btree_delete(keys, data, inserts, fast);
    test_btree_size(0);

    free(data);
    free(keys);

    return 0;
}

int test_btree_random(int inserts, bool fast) {
    engine_reset();

    int max_key_val = inserts * 10;

    long* keys = malloc(inserts * sizeof(long));
    long* data = malloc(inserts * sizeof(long));
    long size = 0;
    for (int i = 0; i < inserts; i += 1) {
        keys[i] = nat_rand(max_key_val);

        int index = index_of(keys[i], keys, i);
        if (index != -1) {
            data[i] = data[index];
        } else {
            data[i] = nat_rand(max_key_val);
            size += 1;
        }

        engine_insert(keys[i], data[i]);
    }

    test_btree_gets(keys, data, size);

    // remove duplicates from keys for delete tests
    long* final_keys = malloc(size * sizeof(long));
    long* final_data = malloc(size * sizeof(long));
    long final_size = 0;
    for (int i = 0; i < inserts; i += 1) {
        if (index_of(keys[i], final_keys, final_size) == -1) {
            final_keys[final_size] = keys[i];
            final_data[final_size] = data[i];
            final_size += 1;
        }
    }

    test_btree_delete(final_keys, final_data, final_size, fast);
    test_btree_size(0);

    free(final_data);
    free(final_keys);
    free(data);
    free(keys);

    return 0;
}

int main(int argc, char* argv[]) {
    time_t t;
    srand((unsigned) time(&t));

    engine_start("test.db");

    printf("Running slow btree_random_no_updates\n");
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random_no_updates(10, false);
        test_btree_random_no_updates(100, false);
        test_btree_random_no_updates(1000, false);
    }

    printf("Slow btree_random_no_updates passed!\n\n");

    printf("Running slow btree_random\n");
    
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random(10, false);
        test_btree_random(100, false);
        test_btree_random(1000, false);
    }

    printf("Slow btree_random passed!\n\n");

    printf("Running fast btree_random_no_updates\n");
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random_no_updates(10, true);
        test_btree_random_no_updates(100, true);
        test_btree_random_no_updates(1000, true);
        test_btree_random_no_updates(10000, true);
    }

    printf("Fast btree_random_no_updates passed!\n\n");

    printf("Running fast btree_random\n");
    
    for (int i = 0; i < REPEAT; i += 1) {
        test_btree_random(10, true);
        test_btree_random(100, true);
        test_btree_random(1000, true);
        test_btree_random(10000, true);
    }

    printf("Fast btree_random passed!\n\n");

    engine_stop();
    
    return 0;
}