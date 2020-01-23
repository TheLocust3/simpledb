#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "database_test.h"
#include "../src/database/database.h"
#include "helpers.h"

void database_test() {
    printf("Running full database tests\n");

    database_initialize("test1.db");

    database_stop();

    printf("Full database tests passed\n");
}
