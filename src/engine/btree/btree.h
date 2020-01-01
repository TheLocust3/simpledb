#ifndef BTREE_H
#define BTREE_H

#define NODES 5
#define CHILDREN 6
#define MIN_CHILDREN 3

typedef struct btree {
    long pid;
    long keys[NODES];
    long data[NODES];
    long children[CHILDREN];
} btree;

btree* btree_malloc();
void btree_free(btree* bt);

long btree_size(btree* bt);
long* btree_keys(btree* bt);
void btree_print(btree* bt);

long btree_get(btree* bt, long key);
btree* btree_insert(btree* bt, long key, long val);
btree* btree_delete(btree* bt, long key);

#endif
