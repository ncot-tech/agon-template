#include <agon/vdp_key.h>
#include <mos_api.h>
#include <stdio.h>
#include "vdp/utils.h"
#include "vdp/graphics.h"
#include "input/keyboard.h"
#include "main_src/colour_bars.h"
#include "main_src/error_screen.h"
#include "debug.h"

volatile SYSVAR *sv;

int main(void)
{
    // Initialise various parts of the system
	sv = vdp_vdu_init();
    if ( vdp_key_init() == -1 ) return 1;
    keyboard_init();

    // You need to do this for every screen in your program
    // See the docs for the screen state machine for more info
    define_screen(colour_bars_init, colour_bars_update, colour_bars_draw);

    // Main loop that quits when ESC is pressed, you can make it not quit if you like
    while (1) {
        keyboard_update();
        if (IS_KEY_PRESSED(KEY_ESC))
            break;

        run_screens();  // You must call this to keep the state machine ticking along
    }

    // This happens when the program has quit
    vdp_set_screen_mode(0);
    vdp_clear_screen();
    vdp_logical_scr_dims( true );
    vdp_cursor_enable( true );
    printf ("Quitting, bye!\n");
    
    return 0;
}

// # vim: set expandtab tabstop=4:
