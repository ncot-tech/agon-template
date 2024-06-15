#include <stdio.h>
#include "colour_bars.h"
#include "../vdp/utils.h"
#include "../vdp/graphics.h"
#include "debug.h"
#include "../input/keyboard.h"
#include "../error.h"

void draw_colour_bars()
{
    uint8_t startx = 32;
    uint8_t starty = 208;
    uint8_t gap = 12; 
    uint8_t size = 56;
    int c = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            vdp_plot_rect(startx+(x*(size+gap)), SCREEN_HEIGHT-(starty+(y*(size+gap))), size, size, c++);
        }
    }
}

void draw_palette()
{
    char *header = "\nA G O N  L I G H T  C O L O U R S\n";
    putch(30); // Homes the cursor without doing anything else to the screen
    printf("%s", header);
    printf  ("=================================\n");
    printf("X 0 1 2 3 4 5 6 7\n\n");
    printf("0\n\n1\n\n2\n\n3\n\n4\n\n5\n\n6\n\n7");
    draw_colour_bars();
}

// Define functions for Screen 1
void colour_bars_init(void) {
    debug_print("colour_bars_init %d\n", 136);
    change_screen_mode(136, 0, 1);
}

int colour_bars_update(void) {
//    if (1) {
//        return 1; // ID of the next screen
//    }

    if (IS_KEY_PRESSED(KEY_SPACE))
        raise_fatal_error("OUT OF CHEESE ERROR", "+++ REDO FROM START +++");

    return -1; // Continue with the current screen
}

void colour_bars_draw(void) {
    vdp_clear_screen();
    draw_palette();
    waitvblank();
    vdp_swap_screen_buffer();
}
