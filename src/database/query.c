#include <stdio.h>
#include <stdlib.h>

#include "query.h"
#include "../log.h"

void query_print(query_request q) {
    if (q.op == QUERY_READ) {
        log_info("[QUERY]: READ %ld\n", q.key);
    } else if (q.op == QUERY_WRITE) {
        log_info("[QUERY]: WRITE %ld %d\n", q.key, q.val);
    } else if (q.op == QUERY_REMOVE) {
        log_info("[QUERY]: REMOVE %ld\n", q.key);
    } else {
        log_error("[QUERY]: Bad query operation %d received\n", q.op);
        abort();
    }
}
