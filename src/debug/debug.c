#include "debug.h"
#include "../maths/xitoa.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t logfile;

void log_init(char *fname)
{
    logfile = mos_fopen(fname, 0x02|0x08);
}

void debug_printf(char *format, ...)
{
    char tmpStr[80];
    va_list argp;
    va_start(argp, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case '%': tmpStr[0] = '%'; tmpStr[1] = 0; break;
                case 'c': tmpStr[0] = va_arg(argp, int); tmpStr[1] = 0; break;
                case 'd': xitoa(va_arg(argp, int), tmpStr, 10); break;
                case 'x': xitoa(va_arg(argp, int), tmpStr, 16); break;
                case 's': strncpy(tmpStr, va_arg(argp, char*), 32); tmpStr[32] = 0; break;
                default : tmpStr[0] = '?';tmpStr[1] = 0; break;
            }
            mos_fwrite(logfile, tmpStr, strlen(tmpStr));
        } else {
            mos_fwrite(logfile, format, 1);
        }
        format++;
    }
    va_end(argp);

  //  
}

void log_message(const char *format, ...) {
    if (logfile == 0) {
        fprintf(stderr, "Log file is not initialized.\n");
        return;
    }

    mos_fwrite(logfile, format, strlen(format));
    //va_list args;
    //va_start(args, format);

    // Get the current time
    
    //fprintf(stderr, "[%ld] %s:%d:%s(): ", sv->time, __FILE__, \
    //                            __LINE__, __func__);

    // Print the log message
    //vfprintf(logfile, format, args);
    //fprintf(logfile, "\n");

    //va_end(args);

    
    //fflush(logfile);
}

