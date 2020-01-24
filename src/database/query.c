#include <stdio.h>
#include <stdlib.h>

#include "query.h"
#include "../log.h"

void query_print(query_request q) {
    if (q.op == QUERY_READ) {
        log_info("%ld: READ %ld\n", q.id, q.key);
    } else if (q.op == QUERY_WRITE) {
        log_info("%ld: WRITE %ld %d\n", q.id, q.key, q.val);
    } else if (q.op == QUERY_REMOVE) {
        log_info("%ld: REMOVE %ld\n", q.id, q.key);
    } else {
        printf("Bad query operation %d received\n", q.op);
        abort();
    }
}
