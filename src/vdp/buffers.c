#include "buffers.h"
#include <stdlib.h>
#include "utils.h"

void vdp_clear_buffer(uint16_t buffer_id)
{
    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(2);
}

void vdp_select_buffer(uint16_t buffer_id)
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

void vdp_consolidate_buffer(uint16_t buffer_id)
{

    putch(23);
    putch(0);
    putch(0xA0);
    write16bit(buffer_id);
    putch(0x0E);

}

void vdp_split_into_cols_from(uint16_t buffer_id, uint16_t width, uint16_t cols,
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

void vdp_split_into_from(uint16_t buffer_id, uint16_t into, uint16_t from)
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

