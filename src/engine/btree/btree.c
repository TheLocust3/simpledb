#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "btree.h"
#include "btree_manager.h"
#include "../../log.h"
#include "../lock_manager/lock_manager.h"

bool is_leaf(btree* bt) {
    if (bt == NULL) {
        return false;
    }

    for (int i = 0; i < CHILDREN; i += 1) {
        if (!btm_is_child_null(bt, i)) {
            return false;
        }
    }

    return true;
} 

bool is_node(btree* bt) {
    if (bt == NULL) {
        return false;
    }

    return !is_leaf(bt);
}

bool is_data_at_empty(btree* bt, int index) {
    return bt->data[index] == -1;
}

bool is_key_at_empty(btree* bt, int index) {
    return bt->keys[index] == -1;
}

btree* btree_malloc() {
    btree* bt = btm_malloc();
    lock_manager_acquire(bt->pid);

    for (int i = 0; i < NODES; i += 1) {
        bt->keys[i] = -1;
        bt->data[i] = -1;
        btm_set_child(bt, i, NULL);
    }

    btm_set_child(bt, CHILDREN - 1, NULL);

    return bt;
}

void btree_free(btree* bt) {
    for (int i = 0; i < CHILDREN; i += 1) {
        if (!btm_is_child_null(bt, i)) {
            btree* tmp = btm_get_child(bt, i);
            btree_free(tmp);
        }
    }

    btm_delete(bt);
}

long node_size(btree* bt) {
    long size = 0;
    if (is_leaf(bt)) {
        for (int i = 0; i < NODES; i += 1) {
            if (!is_data_at_empty(bt, i)) {
                size += 1;
            }
        }
    } else {
        for (int i = 0; i < CHILDREN; i += 1) {
            if (!btm_is_child_null(bt, i)) {
                size += 1;
            }
        }
    }

    return size;
}

long btree_size(btree* bt) {
    long size = 0;
    if (is_leaf(bt)) {
        size += node_size(bt);
    } else {
        for (int i = 0; i < CHILDREN; i += 1) {
            if (!btm_is_child_null(bt, i)) {
                btree* child = btm_get_child(bt, i);
                size += btree_size(child);
                btm_free(child);
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
            if (!btm_is_child_null(bt, i)) {
                btree* child = btm_get_child(bt, i);
                btree_keys_helper(child, keys, offset);
                
                offset += btree_size(child);
                btm_free(child);
            }
        }

        if (!btm_is_child_null(bt, CHILDREN - 1)) {
            btree* child = btm_get_child(bt, CHILDREN - 1);
            btree_keys_helper(child, keys, offset);
            btm_free(child);
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

            if (!btm_is_child_null(bt, i)) {
                btree* child = btm_get_child(bt, i);
                btree_print_helper(child, depth + 1);
                btm_free(child);
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
        for (int i = 0; i < CHILDREN; i += 1) {
            if (key < bt->keys[i]) {
                btree* child = btm_get_child(bt, i);
                long out = btree_get_helper(child, key);
                btm_free(child);

                return out;
            } else if (btm_is_child_null(bt, i)) {
                btree* child = btm_get_child(bt, i - 1);
                long out = btree_get_helper(child, key);
                btm_free(child);

                return out;
            }
        }

        btree* child = btm_get_child(bt, CHILDREN - 1);
        long out = btree_get_helper(child, key);
        btm_free(child);

        return out;
    }

    return -1;
}

long btree_get(btree* bt, long key) {
    log_debug("[BTREE]: btree_get(%ld)\n", key);

    return btree_get_helper(bt, key);
}

btree* btree_split_leaf(btree* bt, long rightmost_key, long rightmost_val) {
    log_debug_level(3, "[BTREE]: Splitting leaf: %ld\n", bt->pid);

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

    btm_set_child(parent, 0, bt);
    btm_set_child(parent, 1, right_node);

    btm_flush(bt);
    btm_free(bt);

    btm_flush(right_node);
    btm_free(right_node);

    btm_flush(parent);

    return parent;
}

btree* btree_split_node(btree* bt, long rightmost_key, btree* rightmost_right_child) {
    log_debug_level(3, "[BTREE]: Splitting node: %ld\n", bt->pid);

    int split_index = NODES / 2 + 1;
    long split_key = bt->keys[split_index];

    btree* right_node = btree_malloc();

     for (int i = split_index; i < NODES; i += 1) {
        right_node->keys[i - split_index] = bt->keys[i + 1];
        btm_set_child_by_child(right_node, i - split_index, bt, i + 1);

        bt->keys[i] = -1;
        btm_set_child(bt, i + 1, NULL);
    }

    right_node->keys[split_index - 2] = rightmost_key;
    btm_set_child(right_node, split_index - 1, rightmost_right_child);

    btree* parent = btree_malloc();
    parent->keys[0] = split_key;
    btm_set_child(parent, 0, bt);
    btm_set_child(parent, 1, right_node);

    btm_flush(bt);
    btm_free(bt);
    
    btm_flush(right_node);
    btm_free(right_node);

    btm_flush(parent);

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

    log_error("[BTREE]: btree_insert_at_leaf failed!\n");
    abort();
}

btree* btree_node_split_handler(btree* parent, btree* maybe_split) {
    if (maybe_split == NULL) {
        return NULL;
    }

    log_debug_level(3, "[BTREE]: Handling split node: %ld with parent: %ld\n", maybe_split->pid, parent->pid);

    int insert_at = -1;
    long inserting_key = maybe_split->keys[0];
    btree* inserting_left_child = btm_get_child(maybe_split, 0);
    btree* inserting_right_child = btm_get_child(maybe_split, 1);

    for (int i = 0; i < NODES; i += 1) {
        if (is_key_at_empty(parent, i)) { // found an empty spot, insert here
            parent->keys[i] = inserting_key;
            btm_set_child(parent, i, inserting_left_child);
            btm_set_child(parent, i + 1, inserting_right_child);

            btm_free(inserting_right_child);
            btm_free(inserting_left_child);

            return NULL;
        } else if (inserting_key < parent->keys[i]) { // key should be inserted right before this
            insert_at = i;

            break;
        }
    }

    for (int i = insert_at; i != -1 && i < NODES; i += 1) {
        if (is_key_at_empty(parent, i)) {
            parent->keys[i] = inserting_key;
            btm_set_child(parent, i, inserting_left_child);
            btm_set_child(parent, i + 1, inserting_right_child);

            btm_free(inserting_right_child);
            btm_free(inserting_left_child);

            return NULL;
        }
        
        long tmp_key = parent->keys[i];
        btree* tmp_right_child = btm_get_child(parent, i + 1);

        // insert key/val at spot, loop again to shift values to the left
        parent->keys[i] = inserting_key;
        btm_set_child(parent, i, inserting_left_child);
        btm_set_child(parent, i + 1, inserting_right_child);

        inserting_key = tmp_key;
        btm_free(inserting_left_child);
        inserting_left_child = inserting_right_child;
        inserting_right_child = tmp_right_child;
    }

    btm_delete(maybe_split); // free the parent node that we didn't use

    // we couldn't find a good spot to insert at so let's split the parent and propagate the split
    if (insert_at == -1 || inserting_key != maybe_split->keys[0]) {
        btree* tmp = btree_split_node(parent, inserting_key, inserting_right_child);

        btm_free(inserting_right_child);
        btm_free(inserting_left_child);
        return tmp;
    }

    log_error("[BTREE]: btree_node_split_handler failed!\n");
    abort();
}

btree* btree_insert_at_node(btree* bt, long key, long val) {
    for (int i = 0; i < NODES; i += 1) {
        if (is_key_at_empty(bt, i)) { // no more keys in this node, traverse down rightmost child
            btree* child = btm_get_child(bt, i);
            btree* tmp = btree_insert_helper(child, key, val);
            
            return tmp;
        } else if (key < bt->keys[i]) {
            btree* child = btm_get_child(bt, i);
            btree* tmp = btree_insert_helper(child, key, val);

            return tmp;
        }
    }

    btree* child = btm_get_child(bt, CHILDREN - 1);
    btree* tmp = btree_insert_helper(child, key, val);

    return tmp;
}

btree* btree_insert_helper(btree* bt, long key, long val) {
    btree* tmp;
    if (is_leaf(bt)) {
        tmp = btree_insert_at_leaf(bt, key, val);
    } else {
        tmp = btree_node_split_handler(bt, btree_insert_at_node(bt, key, val));
    }

    if (tmp == NULL) {
        btm_flush(bt);
        lock_manager_release(bt->pid);
    } else {
        btm_flush(tmp);
        lock_manager_release(tmp->pid);
    }

    return tmp;
}

btree* btree_insert(btree* bt, long key, long val) {
    log_debug("[BTREE]: btree_insert(%ld, %ld)\n", key, val);

    btree* tmp = btree_insert_helper(bt, key, val);

    return tmp == NULL ? bt : tmp;
}

btree* btree_delete_helper(btree* bt, long key);

btree* btree_delete_at_leaf(btree* bt, long key) {
    int delete_at = -1;
    for (int i = 0; i < NODES; i += 1) {
        if (key == bt->keys[i]) {
            delete_at = i;
            break;
        }
    }

    if (delete_at != -1) {
        for (int i = delete_at + 1; i < NODES; i += 1) {
            bt->keys[i - 1] = bt->keys[i];
            bt->data[i - 1] = bt->data[i];
        }

        bt->keys[NODES - 1] = -1;
        bt->data[NODES - 1] = -1;

        if (node_size(bt) < MIN_CHILDREN) {
            return bt; // return the leaf to be caught by it's parent and merged
        }
    }
    
    return NULL;
}

long first_key(btree* bt) {
    if (bt == NULL) {
        return -1;
    }

    if (is_leaf(bt)) {
        return bt->keys[0];
    } else {
        btree* child = btm_get_child(bt, 0);
        long key = first_key(child);
        btm_free(child);

        return key;
    }
}

btree* btree_merge(btree* left, btree* right) {
    log_debug_level(3, "[BTREE]: Merging left: %ld and right: \n", left->pid, right->pid);

    int left_size = node_size(left);
    if (left_size == 0) { // merging right into an empty leaf
        return right;
    }

    for (int i = left_size; i < NODES; i += 1) {
        btree* right_child = btm_get_child(right, i - left_size);

        if (right_child != NULL) {
            left->keys[i - 1] = first_key(right_child);
        } else {
            left->keys[i] = right->keys[i - left_size];
        }

        left->data[i] = right->data[i - left_size];
        btm_set_child(left, i, right_child);

        btm_free(right_child);
    }

    if (is_node(left)) {
        if (left_size + node_size(right) == CHILDREN) { // we only merge up to NODES, just append rightmost child to left
            btm_set_child_by_child(left, CHILDREN - 1, right, node_size(right) - 1);
            left->keys[NODES - 1] = right->keys[node_size(right) - 2];
        }

        // if merging a node, we're missing one key (the first child of the right node)
        // so promote the new child's first key
        btree* child = btm_get_child(left, left_size);
        left->keys[left_size - 1] = first_key(child);
        btm_free(child);
    }

    btm_flush(left);

    return left;
}

btree* btree_delete_at_node(btree* bt, long key) {
    int follow_at = -1;
    for (int i = 0; i < NODES; i += 1) {
        if (key < bt->keys[i]) {
            follow_at = i;
            break;
        } else if (is_key_at_empty(bt, i)) {
            follow_at = i;
            break;
        }
    }

    if (follow_at == -1) {
        follow_at = CHILDREN - 1;
    }

    btree* node = btree_delete_helper(btm_get_child(bt, follow_at), key);

    if (node != NULL) {
        btree* left_sibling = follow_at > 0 ? btm_get_child(bt, follow_at - 1) : NULL;
        btree* right_sibling = follow_at < NODES ? btm_get_child(bt, follow_at + 1) : NULL;

        int max_children = is_leaf(node) ? NODES : CHILDREN;

        int merge_at = -1;
        long separator = -1;
        if (left_sibling != NULL && node_size(node) + node_size(left_sibling) <= max_children) {
            // merge node into left sibling

            btm_set_child(bt, follow_at - 1, btree_merge(left_sibling, node));
            merge_at = follow_at;
            separator = bt->keys[merge_at];
        } else if (right_sibling != NULL && node_size(node) + node_size(right_sibling) <= max_children) {
            // merge node into right siblings
            btree* tmp = btree_merge(node, right_sibling);
            btm_set_child(bt, follow_at, tmp);
            merge_at = follow_at + 1;
            separator = bt->keys[merge_at];
        }

        btm_free(right_sibling);
        btm_free(left_sibling);
        
        if (merge_at != -1) {
            for (int i = merge_at; i < NODES; i += 1) {
                if (btm_is_child_null(bt, i)) {
                    break;
                }

                bt->keys[i] = bt->keys[i + 1];
                bt->data[i] = bt->data[i + 1];
                btm_set_child_by_child(bt, i, bt, i + 1);
            }

            bt->keys[merge_at - 1] = separator;

            bt->keys[NODES - 1] = -1;
            bt->data[NODES - 1] = -1;
            btm_set_child(bt, CHILDREN - 1, NULL);

            btm_flush(bt);

            if (is_node(bt) && node_size(bt) == 1) { // there's only one child, so promote the child and remove bt
                btree* new_bt = btm_get_child(bt, 0);

                btm_delete(bt);

                return new_bt;
            }

            int empty_at = -1;
            for (int i = 0; i < CHILDREN; i += 1) {
                btree* child = btm_get_child(bt, i);
                if (!btm_is_child_null(bt, i) && node_size(child) == 0) {
                    empty_at = i;
                }
                btm_free(child);
            }

            if (empty_at != -1) {
                for (int i = empty_at; i < NODES; i += 1) {
                    if (btm_is_child_null(bt, i)) {
                        break;
                    }

                    bt->keys[i] = bt->keys[i + 1];
                    btm_set_child_by_child(bt, i, bt, i + 1);
                }

                btm_set_child(bt, CHILDREN - 1, NULL);
            }

            return bt;
        } else {
            // no good merge found, just move on

            return NULL;
        }
    }
    
    return NULL;
}

btree* btree_delete_helper(btree* bt, long key) {
    btree* tmp;
    if (is_leaf(bt)) {
        tmp = btree_delete_at_leaf(bt, key);
    } else {
        tmp = btree_delete_at_node(bt, key);
    }

    if (tmp == NULL) {
        btm_flush(bt);
        lock_manager_release(bt->pid);
    } else {
        btm_flush(tmp);
        lock_manager_release(tmp->pid);
    }

    return tmp;
}

btree* btree_delete(btree* bt, long key) {
    log_debug("[BTREE]: btree_delete(%ld)\n", key);

    btree* tmp = btree_delete_helper(bt, key);

    return tmp == NULL ? bt : tmp;
}
