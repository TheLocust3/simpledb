#ifndef LOG_H
#define LOG_H

#define DEBUG 2

void log_debug_level(int level, const char* format, ...);
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_error(const char* format, ...);

#endif
