// page/storage -> btree
// all btree accesses go through these functions
// these functions essentially exist to hide the storage details from the btree algorithms and to
// efficiently manage memory

#include <stdlib.h>

#include "bpage.h"

btree* create_btree() {
    return NULL;   
}

btree* get_btree(long bid) {
    return NULL;
}

void save_btree(long bid, btree* bt) {

}
