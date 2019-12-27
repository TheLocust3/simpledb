#ifndef BPAGE_H
#define BPAGE_H

#include "btree.h"

btree* create_btree();
btree* get_btree(long bid);
void save_btree(long bid, btree* bt);

#endif
