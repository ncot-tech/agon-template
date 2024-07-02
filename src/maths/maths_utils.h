#ifndef __MATHS_UTILS_H
#define __MATHS_UTILS_H

#include <stdlib.h>
#include <math.h>

/**
 * Chooses a random number between two values.
 */
int rand_between(int min, int max); 
/** Maps one range of integers to another.
 */
int map(int original_number, int original_min, int original_max, int target_min, int target_max);
#endif
