#ifndef BTREE_MANAGER_H
#define BTREE_MANAGER_H

#include "btree.h"

btree* btm_malloc();
btree* btm_get_child(btree* bt, int child_idx);
void btm_set_child(btree* bt, int child_idx, btree* child);
void btm_free(btree* bt);

#endif
