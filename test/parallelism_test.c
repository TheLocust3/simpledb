#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#include "parallelism_test.h"
#include "../src/database/database.h"
#include "../src/database/query.h"
#include "../src/engine/storage_engine.h"
#include "helpers.h"

#define PARALLELISM 2
#define INSERTS 5
#define OVERRIDE 1

typedef struct thread_args {
    int id;
} thread_args;


long thread_keys[PARALLELISM][INSERTS] = { { 27, 29, 6, 34, 10 }, { 14, 44, 46, 32, 41 } };
long thread_vals[PARALLELISM][INSERTS] = { { 47, 24, 3, 17, 10 }, { 28, 34, 39, 43, 4 } };

void* insert_thread(void* void_args) {
    thread_args* args = (thread_args*) void_args;

    printf("Starting insert thread %d\n", args->id);

    database_thread_initialize(args->id);

    query_request write;
    write.op = QUERY_WRITE;

    for (int i = 0; i < INSERTS; i += 1) {
        if (OVERRIDE) {
            write.key = thread_keys[args->id][i];
            write.val = thread_vals[args->id][i];
        } else {
            write.key = nat_rand(INSERTS * 10);
            write.val = nat_rand(INSERTS * 10);
        }

        query_response res = database_query(write);
        assert(res.op == QUERY_WRITE);
        assert(res.code == RESPONSE_SUCCESS);
    }

    printf("Thread %d complete\n", args->id);

    return NULL;
}

void parallelism_test() {
    printf("Running parallelism tests\n\n");

    database_initialize("test3.db");
    printf("\n");

    time_t t;
    srand((unsigned) time(&t));

    pthread_t thread[PARALLELISM];
    thread_args** args = malloc(PARALLELISM * sizeof(thread_args*));
    for (int i = 0; i < PARALLELISM; i += 1) {
        args[i] = malloc(sizeof(thread_args));
        args[i]->id = i;
        pthread_create(&thread[i], NULL, insert_thread, args[i]); 
    }

    for (int i = 0; i < PARALLELISM; i += 1) {
        pthread_join(thread[i], NULL);

        free(args[i]);
    }

    free(args);

    printf("\n");
    database_stop();

    printf("\nParallelism tests passed\n");
}
