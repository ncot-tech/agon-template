#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#include <mos_api.h>

typedef struct Globals {
    volatile SYSVAR *sysvars;
} Globals;

extern Globals globals;

#endif