#include "utils.h"
#include <mos_api.h>

void write16bit(int16_t w)
{
    putch(w & 0xFF);    // write LSB
    putch((w >> 8) & 0xFF);        // write MSB    
}
void vdp_swap_screen_buffer()
{
    putch(23); putch(0); putch(0xC3);
}

void vdp_set_screen_mode(uint8_t mode)
{
    putch(22); putch(mode);
}

void vdp_enable_logical_screen_scaling(uint8_t on)
{
    putch(23);
    putch(0);
    putch(0xC0);
    putch((uint8_t) on);
}

void vdp_move_origin(int16_t x, int16_t y)
{
    putch(29); write16bit(x); write16bit(y);
}

void vdp_set_gcol(uint8_t colour)
{
    putch(18);
    putch(0);
    putch(colour);
}

void vdp_clg()
{
    putch(16);
}

void vdp_colour(uint8_t colour)
{
    putch(17);
    putch(colour);
}