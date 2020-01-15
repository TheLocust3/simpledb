// layer between the page manager and the btree algorithms

#include <stdio.h>
#include <stdlib.h>

#include "../lock_manager/lock_manager.h"
#include "../btree/btree_manager.h"
#include "../page_manager/page_manager.h"

btree* btm_malloc() {
    page_id bt_pid = malloc_page();

    btree* bt = get_page(bt_pid);
    bt->pid = bt_pid;

    return bt;
}

bool btm_is_child_null(btree* bt, int child_idx) {
    return bt->children[child_idx] == -1;
}

btree* btm_get_child(btree* bt, int child_idx) {
    lock_manager_acquire(bt->pid);
    page_id child_pid = bt->children[child_idx];

    if (child_pid == -1) {
        return NULL;
    }

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
    flush_page(bt->pid, bt);
}

void btm_delete(btree* bt) {
    lock_manager_release(bt->pid);

    free_page(bt->pid);
    btm_free(bt);
}

void btm_free(btree* bt) {
    if (bt == NULL) return;

    lock_manager_release(bt->pid);

    free(bt);
}
