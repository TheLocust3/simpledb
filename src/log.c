#include <stdio.h>
#include <stdarg.h>

#include "log.h"

void log_debug(const char* format, ...) {
    if (!DEBUG) return;

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}
