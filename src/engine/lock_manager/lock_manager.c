#include <pthread.h>

#include "lock_manager.h"
#include "lock_list.h"
#include "../../log.h"


static lock_list* list = NULL;
static lock_list* special = NULL;

void lock_manager_init() {
    log_debug("[LOCK_MANAGER]: Initializing\n");

    list = lock_list_malloc();

    special = lock_list_malloc();
    special = lock_list_add(special); // lock list
}

void lock_manager_stop() {
    lock_list_free(list);
    list = NULL;

    lock_list_free(special);
    special = NULL;

    log_debug("[LOCK_MANAGER]: Stopped\n");
}

void lock_manager_add(page_id pid) {
    log_debug_level(2, "[LOCK_MANAGER]: Adding lock for page: %ld\n", pid);

    assert(pid <= list->elements, "lock_manager_add: pid <= list->elements");

    lock_manager_acquire_special(LOCK_LIST);

    if (list->elements > pid) { // we've already allocated a lock for this page
        lock_list_reset(list, pid);
    }

    list = lock_list_add(list);

    lock_manager_release_special(LOCK_LIST);
}

void lock_manager_acquire(page_id pid) {
    log_debug_level(2, "[LOCK_MANAGER]: Acquiring lock on page: %ld\n", pid);

    pthread_mutex_lock(lock_list_get(list, pid));
}

void lock_manager_acquire_special(int lock_id) {
    log_debug_level(3, "[LOCK_MANAGER]: Acquiring special lock: %d\n", lock_id);

    pthread_mutex_lock(lock_list_get(special, lock_id));
}

void lock_manager_release(page_id pid) {
    log_debug_level(2, "[LOCK_MANAGER]: Releasing lock on page: %ld\n", pid);

    pthread_mutex_unlock(lock_list_get(list, pid));
}

void lock_manager_release_special(int lock_id) {
    log_debug_level(3, "[LOCK_MANAGER]: Releasing special lock: %d\n", lock_id);

    pthread_mutex_unlock(lock_list_get(special, lock_id));
}
