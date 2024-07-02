#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdlib.h>
#include <math.h>

/**
 * A structure to hold a 2D vector.
 * 
 * This uses floating point variables, so will not be very optimal on anything without an FPU.
 */
typedef struct Vector2 {
    float x; /**< X value */
    float y; /**< Y value */
} Vector2;

/**
 * A structure to hold a 3D vector.
 * 
 * This uses floating point variables, so will not be very optimal on anything without an FPU.
 */
typedef struct Vector3 {
    float x; /**< X value */
    float y; /**< Y value */
    float z; /**< Z value */
} Vector3;

/**
 * Normalises a 2D vector, modifying the vector directly.
 * 
 * This uses floating point division and square root.
 */
void vector2_normalise(Vector2 *v);

#endif