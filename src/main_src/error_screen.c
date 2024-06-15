#include <stdio.h>
#include "error_screen.h"
#include "../vdp/utils.h"
#include "../vdp/graphics.h"
#include "debug.h"

/*
 * You need to add this line to main.c
 * define_screen (error_screen_init, error_screen_update, error_screen_draw);
 */

void error_screen_init(void) {
    debug_print("error_screen_init\n");
    change_screen_mode(0, 1, 1);
    vdp_colour(134);
    vdp_clear_screen();
    
    vdp_colour(1);
    printf("ERROR!\n");
    vdp_colour(0);
    printf("Shit's hit the fan, the program has stopped.\n");
}

int error_screen_update(void) {
    
    return -1; // Continue with the current screen
}

void error_screen_draw(void) {
    
}
