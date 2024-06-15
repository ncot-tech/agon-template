#include <stdio.h>
#include "${PROGNAME}.h"
#include "../vdp/utils.h"
#include "../vdp/graphics.h"
#include "debug.h"

/*
 * You need to add this line to main.c
 * define_screen (${PROGNAME_LOWER}_init, ${PROGNAME_LOWER}_update, ${PROGNAME_LOWER}_draw);
 */

void ${PROGNAME_LOWER}_init(void) {
    debug_print("${PROGNAME}_init\n");
    change_screen_mode(136, 0, 1);
}

int ${PROGNAME_LOWER}_update(void) {
//    if (1) {
//        return 1; // ID of the next screen
//    }
    return -1; // Continue with the current screen
}

void ${PROGNAME_LOWER}_draw(void) {
    vdp_clear_screen();
    draw_palette();
    waitvblank();
    vdp_swap_screen_buffer();
}
