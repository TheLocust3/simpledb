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

    log_debug_level(2, "[BTREE_MANAGER]: Allocated new node at %ld\n", bt->pid);

    return bt;
}

bool btm_is_child_null(btree* bt, int child_idx) {
    return bt->children[child_idx] == -1;
}

btree* btm_get_child(btree* bt, int child_idx) {
    page_id child_pid = bt->children[child_idx];
    log_debug_level(2, "[BTREE_MANAGER]: Getting child: %ld of parent: %ld\n", child_pid, bt->pid);

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
        assert(is_valid_page_id(child->pid), "btm_set_child: is_valid_page_id(child->pid)");
        bt->children[child_idx] = child->pid;
    }
}

void btm_set_child_by_child(btree* bt, int child_idx, btree* new_bt, int new_child_idx) {
    assert(is_valid_page_id(new_bt->children[new_child_idx]), "btm_set_child_by_child: is_valid_page_id(new_bt->children[new_child_idx])");
    bt->children[child_idx] = new_bt->children[new_child_idx];
}

void btm_flush(btree* bt) {
    assert(is_valid_page_id(bt->pid), "btm_flush: is_valid_page_id(bt->pid)");
    log_debug_level(2, "[BTREE_MANAGER]: Flushing btree: %ld\n", bt->pid);

    flush_page(bt->pid, bt);
}

void btm_delete(btree* bt) {
    assert(is_valid_page_id(bt->pid), "btm_delete: is_valid_page_id(bt->pid)");
    log_debug_level(2, "[BTREE_MANAGER]: Deleting btree: %ld\n", bt->pid);

    free_page(bt->pid);
    btm_free(bt);
}

void btm_free(btree* bt) {
    if (bt == NULL) return;

    long pid = bt->pid;
    assert(pid >= 0, "btm_free: bt->pid >= 0");

    log_debug_level(2, "[BTREE_MANAGER]: Freeing btree: %ld\n", pid);

    free(bt);
    // lock_manager_release(pid);
}
