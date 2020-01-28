#ifndef LOG_H
#define LOG_H

#include <stdbool.h>

#define DEBUG 3

void log_init(int id);
void assert(bool assertion, const char* failed_msg);
void log_debug_level(int level, const char* format, ...);
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_error(const char* format, ...);

#endif
