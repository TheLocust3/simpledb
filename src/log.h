#ifndef LOG_H
#define LOG_H

#define DEBUG 1

void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_error(const char* format, ...);

#endif
