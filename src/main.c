#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include "graphics/graphics.h"
#include <math.h>

// https://github.com/AgonConsole8/agon-docs/blob/main/VDP---Screen-Modes.md
#define SC_MODE 136
#define SC_WIDTH 1280
#define SC_HEIGHT 1024


static volatile SYSVAR *sv;

void draw_colour_bars()
{
    uint8_t c = 0;
    for (int y = 0; y < SC_HEIGHT; y+= 16) {
        vdp_plot_rect(c, 0, y, SC_WIDTH, 16);
        c++;
    }
}

int main(void)
{
	
	sv = vdp_vdu_init();
    if ( vdp_key_init() == -1 ) return 1;

    set_video_mode(SC_MODE);
    vdp_clear_screen();
    vdp_logical_scr_dims( true );
    vdp_cursor_enable( false );

	while (1) {
        draw_colour_bars();
        waitvblank();
        flip_buffer();
    }

	return 0;
}

// # vim: set expandtab tabstop=4:
