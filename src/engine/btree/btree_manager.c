// layer between the page manager and the btree algorithms

#include <stdlib.h>

#include "btree_manager.h"
#include "../page_manager.h"

btree* btm_malloc() {
    page_id bt_pid = malloc_page();

    btree* bt = get_page(bt_pid);
    bt->pid = bt_pid;

    return bt;
}

btree* btm_get_child(btree* bt, int child_idx) {
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

void btm_free(btree* bt) {
    free_page(bt->pid);
}
