#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#include "parallelism_test.h"
#include "../src/database/database.h"
#include "../src/database/query.h"
#include "helpers.h"

#define PARALLELISM 5
#define INSERTS 10

void* insert_thread() {
    printf("Starting insert thread\n");

    query_request write;
    write.op = QUERY_WRITE;

    for (int i = 0; i < INSERTS; i += 1) {
        write.key = nat_rand(INSERTS * 10);
        write.val = nat_rand(INSERTS * 10);

        query_response res = database_query(write);
        assert(res.op == QUERY_WRITE);
        assert(res.code == RESPONSE_SUCCESS);
    }

    return NULL;
}

void parallelism_test() {
    printf("Running parallelism tests\n\n");

    database_initialize("test3.db");
    printf("\n");

    time_t t;
    srand((unsigned) time(&t));

    pthread_t thread[PARALLELISM];
    for (int i = 0; i < PARALLELISM; i += 1) {
        pthread_create(&thread[i], NULL, insert_thread, NULL); 
    }

    for (int i = 0; i < PARALLELISM; i += 1) {
        pthread_join(thread[i], NULL);
    }

    printf("\n");
    database_stop();

    printf("\nParallelism tests passed\n");
}
