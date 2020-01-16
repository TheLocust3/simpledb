#include <pthread.h>
#include <assert.h>

#include "lock_manager.h"
#include "../../log.h"

static pthread_mutex_t lock;

void lock_manager_init() {
    log_debug("Initializing lock manager\n");

    int rv = pthread_mutex_init(&lock, NULL);
    assert(rv == 0);


}

void lock_manager_reset() {
    log_debug("Reseting lock manager\n");
}

void lock_manager_stop() {
    log_debug("Lock manager stopped\n");
}

void lock_manager_acquire(page_id pid) {
    log_debug_level(2, "Acquiring lock on page: %ld\n", pid);

    // pthread_mutex_lock(&lock);
}

void lock_manager_release(page_id pid) {
    log_debug_level(2, "Releasing lock on page: %ld\n", pid);

    // pthread_mutex_unlock(&lock);
}
