#include <stdio.h>
#include <stdlib.h>

#include "query.h"
#include "../log.h"

void query_print(query_request q) {
    if (q.op == QUERY_READ) {
        log_info("READ %d\n", q.key);
    } else if (q.op == QUERY_WRITE) {
        log_info("WRITE %d %d\n", q.key, q.val);
    } else if (q.op == QUERY_REMOVE) {
        log_info("REMOVE %d\n", q.key);
    } else {
        printf("Bad query operation %d received\n", q.op);
        abort();
    }
}
