#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <mos_api.h>

extern volatile SYSVAR *sv;

#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "[%ld] %s:%d:%s(): " fmt, sv->time, __FILE__, \
                                __LINE__, __func__, ##__VA_ARGS__); } while (0)

void log_init(char *fname);
void log_message(const char *format, ...);
void debug_printf(char *format, ...);

#endif