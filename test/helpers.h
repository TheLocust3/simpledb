#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static int index_of(int data, long* arr, int size) {
    for (int i = 0; i < size; i += 1) {
        if (data == arr[i]) {
            return i;
        }
    }

    return -1;
}

static bool includes(int data, long* arr, int size) {
    return index_of(data, arr, size) == -1 ? false : true;
}

static long nat_rand(int upper_bound) {
    long val = rand() % upper_bound;
    
    return val >= 0 ? val : nat_rand(upper_bound);
}

static clock_t start_time;

static void start_timer() {
    start_time = clock();
}

static void stop_timer() {
    clock_t end_time = clock();

    double diff = ((double) (end_time - start_time) / 1000000.0F ) * 1000;
    printf("took %.2fms\n", diff);
}

#endif