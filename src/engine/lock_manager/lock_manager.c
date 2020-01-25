#include <pthread.h>
#include <assert.h>

#include "lock_manager.h"
#include "lock_list.h"
#include "../../log.h"


static lock_list* list = NULL;
static lock_list* special = NULL;

void lock_manager_init() {
    log_debug("Initializing lock manager\n");

    list = lock_list_malloc();
    special = lock_list_malloc();

    special = lock_list_add(special);
}

void lock_manager_stop() {
    lock_list_free(list);
    list = NULL;

    lock_list_free(special);
    special = NULL;

    log_debug("Lock manager stopped\n");
}

void lock_manager_add(page_id pid) {
    log_debug_level(2, "Adding lock for page: %ld\n", pid);

    assert(pid <= list->elements);

    if (list->elements > pid) { // we've already allocated a lock for this page
        lock_list_reset(list, pid);
    }

    list = lock_list_add(list);
}

void lock_manager_acquire(page_id pid) {
    log_debug_level(2, "Acquiring lock on page: %ld\n", pid);

    pthread_mutex_lock(lock_list_get(list, pid));
}

void lock_manager_acquire_special(int lock_id) {
    log_debug_level(2, "Acquiring special lock: %d\n", lock_id);

    pthread_mutex_lock(lock_list_get(special, lock_id));
}

void lock_manager_release(page_id pid) {
    log_debug_level(2, "Releasing lock on page: %ld\n", pid);

    pthread_mutex_unlock(lock_list_get(list, pid));
}

void lock_manager_release_special(int lock_id) {
    log_debug_level(2, "Releasing special lock: %d\n", lock_id);

    pthread_mutex_unlock(lock_list_get(special, lock_id));
}
