#include <stdio.h>
#include <stdarg.h>

#include "log.h"

__thread int thread_id = -1;

void log_init(int id) {
    thread_id = id;
}

void log_debug_level(int level, const char* format, ...) {
    if (level > DEBUG) return;

    va_list args;
    va_start(args, format);

    char with_id[256];
    sprintf(with_id, "[%d] %s", thread_id, format);

    vprintf(with_id, args);

    va_end(args);
}

void log_debug(const char* format, ...) {
    if (DEBUG <= 0) return;

    va_list args;
    va_start(args, format);

    char with_id[256];
    sprintf(with_id, "[%d] %s", thread_id, format);

    vprintf(with_id, args);

    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char with_id[256];
    sprintf(with_id, "[%d] %s", thread_id, format);

    vprintf(with_id, args);

    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char with_id[256];
    sprintf(with_id, "[%d] %s", thread_id, format);

    vprintf(with_id, args);

    va_end(args);
}
