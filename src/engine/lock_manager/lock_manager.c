#include <pthread.h>
#include <assert.h>

#include "lock_manager.h"
#include "lock_list.h"
#include "../../log.h"

static lock_list* list = NULL;

void lock_manager_init() {
    log_debug("Initializing lock manager\n");

    list = lock_list_malloc();
}

void lock_manager_stop() {
    lock_list_free(list);

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
