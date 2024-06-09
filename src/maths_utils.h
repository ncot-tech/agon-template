#ifndef __MATHS_UTILS_H
#define __MATHS_UTILS_H

#include <stdlib.h>
#include <math.h>

typedef struct vector2 {
    float x, y;
} vector2;

typedef struct vector3 {
    float x, y, z;
} vector3;

void normalise_vector(vector2 *v);
int rand_between(int min, int max); 
int map(int original_number, int original_min, int original_max, int target_min, int target_max);
#endif
