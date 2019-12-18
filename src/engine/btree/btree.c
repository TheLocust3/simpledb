#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "btree.h"

bool is_leaf(btree* bt) {
    for (int i = 0; i < CHILDREN; i += 1) {
        if (bt->children[i] != NULL) {
            return false;
        }
    }

    return true;
} 

bool is_node(btree* bt) {
    return !is_leaf(bt);
}

bool is_data_at_empty(btree* bt, int index) {
    return bt->data[index] == -1;
}

bool is_child_at_empty(btree* bt, int index) {
    return bt->children[index] == NULL;
}

btree* btree_malloc() {
    btree* bt = malloc(sizeof(btree));

    for (int i = 0; i < NODES; i += 1) {
        bt->keys[i] = -1;
        bt->data[i] = -1;
        bt->children[i] = NULL;
    }

    return bt;
}

void btree_free(btree* bt) {
    free(bt);
}

long btree_size(btree* bt) {
    long size = 0;
    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_data_at_empty(bt, i)) {
                size += 1;
            }
        }
    } else {
        for (int i = 0; i < CHILDREN; i += 1) {
            size += btree_size(bt->children[i]);
        }
    }

    return size;
}

long* btree_keys(btree* bt) {
    long* keys = malloc(btree_size(bt) * sizeof(long));

    int offset = 0;
    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_data_at_empty(bt, i)) {
                keys[offset] = bt->keys[i];

                offset += 1;
            }
        }
    } else {
        printf("Implement for nodes\n");
        abort();
    }

    return keys;
}

void btree_print_helper(btree* bt, int depth) {
    int spaces = (depth + 1) * 2;
    char* spacer = malloc((spaces + 1) * sizeof(char));
    for (int i = 0; i < spaces; i += 1) {
        spacer[i] = ' ';
    }
    spacer[spaces + 1] = '\0';

    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            printf("%s%ld: %ld\n", spacer, bt->keys[i], bt->data[i]);
        }
    } else {
        printf("Implement dump for nodes");
        abort();
    }
}

void btree_print(btree* bt) {
    printf("DUMP BTREE\n");
    printf("==========\n");

    btree_print_helper(bt, 0);
}

long btree_get(btree* bt, long key) {
    printf("btree_get(%ld)\n", key);

    return -1;
}

btree* btree_insert_at_leaf(btree* bt, long key, long val) {
    int insert_at = -1;
    for (int i = 0; i < NODES; i += 1) {
        if (key == bt->keys[i]) { // found key, replace value
            bt->data[i] = val;

            return NULL;
        } else if (is_data_at_empty(bt, i)) { // found an empty spot, insert here
            bt->keys[i] = key;
            bt->data[i] = val;
            

            return NULL;
        } else if (key < bt->keys[i]) { // key should be inserted right before this
            insert_at = i;

            break;
        }
    }

    long inserting_key = key;
    long inserting_val = val;
    for (int i = insert_at; i < NODES; i += 1) {
        if (bt->data[i] == -1) {
            bt->keys[i] = inserting_key;
            bt->data[i] = inserting_val;

            return NULL;
        }
        
        long tmp_key = bt->keys[i];
        long tmp_val = bt->data[i];

        // insert key/val at spot, loop again to shift values to the left
        bt->keys[i] = inserting_key;
        bt->data[i] = inserting_val;

        inserting_key = tmp_key;
        inserting_val = tmp_val;
    }

    if (inserting_key != key) {
        // there was overflow, need to split
        printf("Need to implement splitting\n");
        abort();
    }

    return NULL;
}

btree* btree_insert_at_node(btree* bt, long key, long val) {
    return bt;
}

btree* btree_insert(btree* bt, long key, long val) {
    printf("btree_insert(%ld, %ld)\n", key, val);

    btree* tmp;
    if (is_leaf(bt)) {
        tmp = btree_insert_at_leaf(bt, key, val);
    } else {
        tmp = btree_insert_at_node(bt, key, val);
    }

    return tmp == NULL ? bt : tmp;
}

btree* btree_delete(btree* bt, long key) {
    printf("btree_delete(%ld)\n", key);

    return bt;
}
