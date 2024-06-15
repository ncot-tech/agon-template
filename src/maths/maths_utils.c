#include "maths_utils.h"

int rand_between(int min, int max) {
    return min + rand() % (max - min + 1);
}



int map(int original_number, int original_min, int original_max, int target_min, int target_max) {
    return ((target_max - target_min) * (original_number - original_min) / (original_max - original_min)) + target_min;
}


