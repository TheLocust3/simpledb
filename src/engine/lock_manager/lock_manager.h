#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

#include "../page_manager/page_manager.h"

#define LOCK_LIST_LOCK 0
#define FILE_LOCK 1
#define GLOBAL_LOCK 2 // USED FOR TESTING PURPOSES ONLY

void lock_manager_init();
void lock_manager_stop();
void lock_manager_add(page_id pid);
void lock_manager_acquire(page_id pid);
void lock_manager_acquire_special(int lock_id);
void lock_manager_release(page_id pid);
void lock_manager_release_special(int lock_id);

#endif
