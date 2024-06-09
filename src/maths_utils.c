#include "maths_utils.h"

int rand_between(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to normalize a vector
void normalise_vector(vector2 *v) {
    float magnitude = sqrt((v->x) * (v->x) + (v->y) * (v->y));
    v->x /= magnitude;
    v->y /= magnitude;
}

int map(int original_number, int original_min, int original_max, int target_min, int target_max) {
    return ((target_max - target_min) * (original_number - original_min) / (original_max - original_min)) + target_min;
}


