// layer between the page manager and the btree algorithms

#include <stdio.h>
#include <stdlib.h>

#include "../../log.h"
#include "../lock_manager/lock_manager.h"
#include "../btree/btree_manager.h"
#include "../page_manager/page_manager.h"

btree* btm_malloc() {
    page_id bt_pid = malloc_page();
    lock_manager_add(bt_pid);

    btree* bt = get_page(bt_pid);
    bt->pid = bt_pid;

    return bt;
}

bool btm_is_child_null(btree* bt, int child_idx) {
    return bt->children[child_idx] == -1;
}

btree* btm_get_child(btree* bt, int child_idx) {
    page_id child_pid = bt->children[child_idx];

    if (child_pid == -1) {
        return NULL;
    }

    lock_manager_acquire(child_pid);
    void* pg = get_page(child_pid);
    return (btree *) pg;
}

void btm_set_child(btree* bt, int child_idx, btree* child) {
    if (child == NULL) {
        bt->children[child_idx] = -1;
    } else {
        bt->children[child_idx] = child->pid;
    }
}

void btm_set_child_by_child(btree* bt, int child_idx, btree* new_bt, int new_child_idx) {
    bt->children[child_idx] = new_bt->children[new_child_idx];
}

void btm_flush(btree* bt) {
    log_debug_level(2, "[BTREE_MANAGER]: Flushing btree: %ld\n", bt->pid);

    flush_page(bt->pid, bt);
}

void btm_delete(btree* bt) {
    log_debug_level(2, "[BTREE_MANAGER]: Deleting btree: %ld\n", bt->pid);

    free_page(bt->pid);
    btm_free(bt);

    lock_manager_release(bt->pid);
}

void btm_free(btree* bt) {
    if (bt == NULL) return;

    log_debug_level(2, "[BTREE_MANAGER]: Freeing btree: %ld\n", bt->pid);

    free(bt);
    lock_manager_release(bt->pid);
}
