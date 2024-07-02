#include "bitmaps.h"
#include <mos_api.h>
#include <stdlib.h>
#include "buffers.h"
#include "utils.h"
#include "../debug/debug.h"

BITMAP_LOAD_RESULT load_bitmap_into_buffer_fp(uint16_t buffer_id, uint8_t file, Bitmap_header *header_data)
{
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

    vdp_clear_buffer(buffer_id);

    char *buf = (char *)malloc(sizeof(char) * header_data->width);
    if (!buf) {
        return MALLOC_FAIL;
    }
    for (int q = 0; q < header_data->height; q++) {
        mos_fread(file, buf, header_data->width);
        add_stream_to_buffer(buffer_id, buf, header_data->width);
    }

    return SUCCESS;
}

BITMAP_LOAD_RESULT load_bitmap_into_buffer(uint16_t buffer_id, char *filename, Bitmap_header *header_data)
{
    BITMAP_LOAD_RESULT res = SUCCESS;

    uint8_t file = mos_fopen(filename, 0x01);
    if (!file) {
        return BAD_FILE;
    }

    res = load_bitmap_into_buffer_fp(buffer_id, file, header_data);
    
    mos_fclose(file);
    return res;
}

void vdp_draw_current_bitmap(uint16_t x, uint16_t y)
{

    putch(23);
    putch(27);
    putch(3);
    write16bit(x);
    write16bit(y);

}

void vdp_assign_buffer_to_bitmap(uint16_t buffer_id, BITMAP_FORMAT bitmap_format,
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

void debug_print_bitmap(Bitmap_header *header)
{
    debug_printf("Bitmap width %d, height %d, bpp %d\n",
        header->width, header->height, header->bpp);
}