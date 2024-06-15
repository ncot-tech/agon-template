#include "vector.h"

// Function to normalize a vector
void vector2_normalise(Vector2 *v) {
    float magnitude = sqrt((v->x) * (v->x) + (v->y) * (v->y));
    v->x /= magnitude;
    v->y /= magnitude;
}