#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <mos_api.h>

void
vdp_draw_line(int16_t origin_x, int16_t origin_y, int16_t end_x,
      int16_t end_y, uint8_t colour)
{

    putch(18);
    putch(0);
    putch(colour);

    putch(25);
    putch(4);
    write16bit(origin_x);
    write16bit(origin_y);

    putch(25);
    putch(5);
    write16bit(end_x);
    write16bit(end_y);

}

void vdp_plot_circle(uint16_t x, uint16_t y, uint16_t diameter, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(4); write16bit(x); write16bit(y);
    putch(25); putch(153); write16bit(0); write16bit(diameter);
}

void vdp_draw_triangle(Point p1, Point p2, Point p3, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(4); write16bit(p1.x); write16bit(p1.y);
    putch(25); putch(4); write16bit(p2.x); write16bit(p2.y);
    putch(25); putch(85); write16bit(p3.x); write16bit(p3.y);
}

void vdp_plot_point(uint16_t x, uint16_t y, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(69);
    write16bit(x); write16bit(y);
}

void vdp_plot_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(4); write16bit(x); write16bit(y);
    putch(25); putch(97); write16bit(w); write16bit(h);
}

void vdp_plot_bitmap(uint16_t buffer_id, int16_t x, int16_t y)
{
    putch(23); putch(27); putch(0x20); write16bit(buffer_id);
    putch(25); putch(0xED); write16bit(x); write16bit(y);
}
