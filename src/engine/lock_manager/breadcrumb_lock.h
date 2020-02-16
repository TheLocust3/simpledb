#ifndef BREADCRUMB_LOCK_H
#define BREADCRUMB_LOCK_H

#include "../../common/linked_list.h"
#include "../btree/btree.h"

typedef list breadcrumb_list;


breadcrumb_list* breadcrumb_lock_malloc();
void breadcrumb_lock_free(breadcrumb_list* list);

breadcrumb_list* breadcrumb_lock_push(breadcrumb_list* list, long pid);
breadcrumb_list* breadcrumb_lock_pop(breadcrumb_list* list);

#endif
