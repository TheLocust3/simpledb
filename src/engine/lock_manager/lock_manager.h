#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

#include "../page_manager/page_manager.h"

void lock_manager_init();
void lock_manager_reset();
void lock_manager_stop();
void lock_manager_acquire(page_id pid);
void lock_manager_release(page_id pid);

#endif
