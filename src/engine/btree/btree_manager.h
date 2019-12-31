#ifndef BTREE_MANAGER_H
#define BTREE_MANAGER_H

#include <stdbool.h>

#include "btree.h"

btree* btm_malloc();
bool btm_is_child_null(btree* bt, int child_idx);
btree* btm_get_child(btree* bt, int child_idx);
void btm_set_child(btree* bt, int child_idx, btree* child);
void btm_set_child_by_child(btree* bt, int child_idx, btree* new_bt, int new_child_idx);
void btm_free(btree* bt);

#endif
