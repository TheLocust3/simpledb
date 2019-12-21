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

bool is_key_at_empty(btree* bt, int index) {
    return bt->keys[index] == -1;
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

    bt->children[CHILDREN - 1] = NULL;

    return bt;
}

void btree_free(btree* bt) {
    for (int i = 0; i < CHILDREN; i += 1) {
        if (!is_child_at_empty(bt, i)) {
            btree_free(bt->children[i]);
        }
    }

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
            if (!is_child_at_empty(bt, i)) {
                size += btree_size(bt->children[i]);
            }
        }
    }

    return size;
}

void btree_keys_helper(btree* bt, long* keys, int offset) {
    if (bt == NULL) {
        return;
    }

    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_key_at_empty(bt, i)) {
                keys[offset] = bt->keys[i];

                offset += 1;
            }
        }
    } else {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_child_at_empty(bt, i)) {
                btree_keys_helper(bt->children[i], keys, offset);
                
                offset += btree_size(bt->children[i]);
            }
        }

        if (!is_child_at_empty(bt, CHILDREN - 1)) {
            btree_keys_helper(bt->children[CHILDREN - 1], keys, offset);
        }
    }
}

long* btree_keys(btree* bt) {
    long* keys = malloc(btree_size(bt) * sizeof(long));

    btree_keys_helper(bt, keys, 0);

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
        for (int i = 0; i < CHILDREN; i += 1) {
            if (i > 0) {
                printf("%s%ld - separator\n", spacer, bt->keys[i - 1]);
            }

            if (!is_child_at_empty(bt, i)) {
                btree_print_helper(bt->children[i], depth + 1);
            }
        }
    }
}

void btree_print(btree* bt) {
    printf("\nDUMP BTREE\n");
    printf("==========\n");

    btree_print_helper(bt, 0);
    printf("\n");
}

long btree_get_helper(btree* bt, long key) {
    if (bt == NULL) {
        return -1;
    }

    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_key_at_empty(bt, i) && key == bt->keys[i]) {
                return bt->data[i];
            }
        }
    } else {
        for (int i = 0; i < NODES; i += 1) {
            if (key < bt->keys[i]) {
                return btree_get_helper(bt->children[i], key);
            } else if (is_child_at_empty(bt, i)) {
                return btree_get_helper(bt->children[i - 1], key);
            }
        }

        return btree_get_helper(bt->children[CHILDREN - 1], key);
    }

    return -1;
}

long btree_get(btree* bt, long key) {
    printf("btree_get(%ld)\n", key);

    return btree_get_helper(bt, key);
}

btree* btree_split_leaf(btree* bt, long rightmost_key, long rightmost_val) {
    int split_index = NODES / 2 + 1;
    long split_key = bt->keys[split_index];

    btree* right_node = btree_malloc();

     for (int i = split_index; i < NODES; i += 1) {
        right_node->keys[i - split_index] = bt->keys[i];
        right_node->data[i - split_index] = bt->data[i];

        bt->keys[i] = -1;
        bt->data[i] = -1;
    }

    right_node->keys[split_index - 1] = rightmost_key;
    right_node->data[split_index - 1] = rightmost_val;

    btree* parent = btree_malloc();
    parent->keys[0] = split_key;
    parent->children[0] = bt;
    parent->children[1] = right_node;

    return parent;
}

btree* btree_split_node(btree* bt, long rightmost_key, btree* rightmost_right_child) {
    int split_index = NODES / 2 + 1;
    long split_key = bt->keys[split_index];

    btree* right_node = btree_malloc();

     for (int i = split_index; i < NODES; i += 1) {
        right_node->keys[i - split_index] = bt->keys[i + 1];
        right_node->children[i - split_index] = bt->children[i + 1];

        bt->keys[i] = -1;
        bt->children[i + 1] = NULL;
    }

    right_node->keys[split_index - 2] = rightmost_key;
    right_node->children[split_index - 1] = rightmost_right_child;

    btree* parent = btree_malloc();
    parent->keys[0] = split_key;
    parent->children[0] = bt;
    parent->children[1] = right_node;

    return parent;
}

btree* btree_insert_helper(btree* bt, long key, long val);

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
    for (int i = insert_at; i != -1 && i < NODES; i += 1) {
        if (is_data_at_empty(bt, i)) {
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

    // if we end up with a different key than the initial key or we didn't find a good spot to
    // insert at, split the node and insert the key we have to the right
    if (insert_at == -1 || inserting_key != key) {
        return btree_split_leaf(bt, inserting_key, inserting_val);
    }

    printf("btree_insert_at_leaf failed!\n");
    abort();
}

btree* btree_node_split_handler(btree* parent, btree* maybe_split) {
    if (maybe_split == NULL) {
        return NULL;
    }

    // TODO: below code copied (a mildly modified) from btree_insert_at_leaf

    int insert_at = -1;
    long inserting_key = maybe_split->keys[0];
    btree* inserting_left_child = maybe_split->children[0];
    btree* inserting_right_child = maybe_split->children[1];

    for (int i = 0; i < NODES; i += 1) {
        if (is_key_at_empty(parent, i)) { // found an empty spot, insert here
            parent->keys[i] = inserting_key;
            parent->children[i] = inserting_left_child;
            parent->children[i + 1] = inserting_right_child;

            return NULL;
        } else if (inserting_key < parent->keys[i]) { // key should be inserted right before this
            insert_at = i;

            break;
        }
    }

    for (int i = insert_at; i != -1 && i < NODES; i += 1) {
        if (is_key_at_empty(parent, i)) {
            parent->keys[i] = inserting_key;
            parent->children[i] = inserting_left_child;
            parent->children[i + 1] = inserting_right_child;

            return NULL;
        }
        
        long tmp_key = parent->keys[i];
        btree* tmp_right_child = parent->children[i + 1];

        // insert key/val at spot, loop again to shift values to the left
        parent->keys[i] = inserting_key;
        parent->children[i] = inserting_left_child;
        parent->children[i + 1] = inserting_right_child;

        inserting_key = tmp_key;
        inserting_left_child = inserting_right_child;
        inserting_right_child = tmp_right_child;
    }

    free(maybe_split); // free the parent node that we didn't use

    // we couldn't find a good spot to insert at so let's split the parent and propagate the split
    if (insert_at == -1 || inserting_key != maybe_split->keys[0]) {
        return btree_split_node(parent, inserting_key, inserting_right_child);
    }

    printf("btree_node_split_handler failed!\n");
    abort();
}

btree* btree_insert_at_node(btree* bt, long key, long val) {
    for (int i = 0; i < NODES; i += 1) {
        if (is_key_at_empty(bt, i)) { // no more keys in this node, traverse down rightmost child
            return btree_insert_helper(bt->children[i], key, val);
        } else if (key < bt->keys[i]) {
            return btree_insert_helper(bt->children[i], key, val);
        }
    }

    return btree_insert_helper(bt->children[CHILDREN - 1], key, val);
}

btree* btree_insert_helper(btree* bt, long key, long val) {
    btree* tmp;
    if (is_leaf(bt)) {
        return btree_insert_at_leaf(bt, key, val);
    }

    return btree_node_split_handler(bt, btree_insert_at_node(bt, key, val));
}

btree* btree_insert(btree* bt, long key, long val) {
    printf("btree_insert(%ld, %ld)\n", key, val);

    btree* tmp = btree_insert_helper(bt, key, val);

    return tmp == NULL ? bt : tmp;
}

btree* btree_delete(btree* bt, long key) {
    printf("btree_delete(%ld)\n", key);

    return bt;
}
