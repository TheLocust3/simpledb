#include "lock_manager.h"
#include "../../log.h"

void lock_manager_acquire(page_id pid) {
    log_debug_level(2, "Acquiring lock on page: %ld\n", pid);
}

void lock_manager_release(page_id pid) {
    log_debug_level(2, "Releasing lock on page: %ld\n", pid);
}
