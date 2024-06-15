#ifndef __DEBUG_H_
#define __DEBUG_H_

extern volatile SYSVAR *sv;

#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "[%ld] %s:%d:%s(): " fmt, sv->time, __FILE__, \
                                __LINE__, __func__, ##__VA_ARGS__); } while (0)

#endif