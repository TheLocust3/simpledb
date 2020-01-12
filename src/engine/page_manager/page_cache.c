// small page cache used by page_manager before checking for the page on disk

#include <stdio.h>
#include <stdlib.h>

#include "page_cache.h"

static page_node* cache = NULL;
static int page_list_size = 0;

bool page_cache_add(long pid, void* mem) {
    page_node* page = (page_node*) mem;

    // TODO: use a real algorithm for this, not Jake's super inefficient caching TM
    if (page_list_size <= MAX_PAGE_CACHE_SIZE) {
        page->pid = pid;
        page->next = cache;

        cache = page;
        page_list_size += 1;

        return true;
    }

    return false;
}

void page_cache_remove(long pid) {
    page_node* prev_page = NULL;
    page_node* on_page = cache;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            if (prev_page == NULL) {
                page_node* tmp = cache;
                cache = cache->next;
                free(tmp);
                
                return;
            }

            prev_page->next = on_page->next;
            free(on_page);

            return;
        }

        prev_page = on_page;
        on_page = on_page->next;
    }
}

void* page_cache_get(long pid) {
    page_node* on_page = cache;
    while (on_page != NULL) {
        if (on_page->pid == pid) {
            return (void*) (((char *) on_page) + sizeof(page_node));
        }

        on_page = on_page->next;
    }

    return NULL;
}
