#include <stdio.h>

#include "database_test.h"
#include "parallelism_test.h"
#include "engine_test.h"

int main(int argc, char* argv[]) {
    printf("Running all tests\n\n\n");

    // database_test();

    printf("\n\n");

    parallelism_test();

    printf("\n\n");

    // engine_test();

    printf("\n\nALL TESTS PASSED\n");
    
    return 0;
}
