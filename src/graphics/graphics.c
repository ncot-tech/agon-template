//#include "globals.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

void write16bit(int16_t w)
{
    putch(w & 0xFF);    // write LSB
    putch((w >> 8) & 0xFF);        // write MSB    
}

void set_video_mode(uint8_t mode)
{
    putch(22); putch(mode);
}

void flip_buffer()
{
    putch(23); putch(0); putch(0xC3);
}

void vdp_move_origin(int16_t x, int16_t y)
{
    putch(29); write16bit(x); write16bit(y);
}

void
draw_line(int16_t origin_x, int16_t origin_y, int16_t end_x,
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

void plot_circle(uint16_t x, uint16_t y, uint16_t diameter, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(4); write16bit(x); write16bit(y);
    putch(25); putch(153); write16bit(0); write16bit(diameter);
}

void draw_triangle(Point p1, Point p2, Point p3, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(4); write16bit(p1.x); write16bit(p1.y);
    putch(25); putch(4); write16bit(p2.x); write16bit(p2.y);
    putch(25); putch(85); write16bit(p3.x); write16bit(p3.y);
}

void plot_point(uint16_t x, uint16_t y, uint8_t colour)
{
    putch(18); putch(0); putch(colour);
    putch(25); putch(69);
    write16bit(x); write16bit(y);
}

void gcol(uint8_t colour)
{
    putch(18);
    putch(0);
    putch(colour);
}

void switch_logical(bool on)
{

    putch(23);
    putch(0);
    putch(0xC0);
    putch((uint8_t) on);

}

bitmap_load_result load_bitmap_into_buffer(uint16_t buffer_id, char *filename, ncotb_header *header_data)
{

    uint8_t file = mos_fopen(filename, 0x01);
    if (!file) {
        return BAD_FILE;
    }

    if (!header_data) {
        return MALLOC_FAIL;
    }

    mos_fread(file, (char *)header_data, 10);
    if (header_data->id[0] != 'N' || header_data->id[1] != 'C' || header_data->id[2] != 'O'
        || header_data->id[3] != 'T' || header_data->id[4] != 'B') {
        return NOT_IMAGE;
    }

    if (header_data->bpp != 1) {
        return WRONG_BPP;
    }

    clear_buffer(buffer_id);

    char *buf = (char *)malloc(sizeof(char) * header_data->width);
    if (!buf) {
        return MALLOC_FAIL;
    }
    for (int q = 0; q < header_data->height; q++) {
        mos_fread(file, buf, header_data->width);
        add_stream_to_buffer(buffer_id, buf, header_data->width);
//        for (int p = 0; p < header->width; p++) {
//            // And then turn it back into RGBA bytes for now
//            putch(((buf[p] >> 6) & 0x03) * 64);    // R
//            putch(((buf[p] >> 4) & 0x03) * 64);    // G
//            putch(((buf[p] >> 2) & 0x03) * 64);    // B
//            putch((buf[p] & 0x03) * 64);    // A
//        }
    }
    mos_fclose(file);
    return SUCCESS;
}

void clear_buffer(uint16_t buffer_id)
{

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(2);

}

void select_buffer(uint24_t buffer_id)
{

    putch(23);
    putch(27);
    putch(0x20);
    write16bit(buffer_id);

}

void add_stream_to_buffer(uint16_t buffer_id, char *buffer_content,
              uint16_t buffer_size)
{

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(0);
    write16bit(buffer_size);

    mos_puts(buffer_content, buffer_size, 0);

}

void vdp_extended_select(uint16_t buffer_id)
{

    putch(23);
    putch(27);
    putch(0x20);
    write16bit(buffer_id);

}

void vdp_draw(uint16_t x, uint16_t y)
{

    putch(23);
    putch(27);
    putch(3);
    write16bit(x);
    write16bit(y);

}

void consolidate_buffer(uint16_t buffer_id)
{

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(0x0E);

}

void split_into_from(uint16_t buffer_id, uint16_t into, uint16_t from)
{

    //VDU 23, 0, &A0, bufferId; 17, blockSize; targetBufferId;

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(17);
    write16bit(into);
    write16bit(from);

}

void split_into_cols_from(uint16_t buffer_id, uint16_t width, uint16_t cols,
              uint16_t from)
{

    //VDU 23, 0, &A0, bufferId; 20, width; blockCount; targetBufferId;

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(20);
    write16bit(width);
    write16bit(cols);
    write16bit(from);

}

void assign_buffer_to_bitmap(uint16_t buffer_id, BITMAP_FORMAT bitmap_format,
                 uint16_t width, uint16_t height)
{

    vdp_extended_select(buffer_id);
    //Consolidate buffer: (if needed) VDU 23, 0, &A0, bufferId; &0C

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(0x0E);
    //Create bitmap from buffer: VDU 23, 27, &21, bufferId; format, width; height;
    
    putch(23);
    putch(27);
    putch(0x21);
    //write16bit(buffer_id);
    write16bit(width);
    write16bit(height);
    putch(bitmap_format);
}

void vdp_plot_rect(uint8_t colour, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
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
