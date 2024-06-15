#ifndef __VDP_BITMAPS_H_
#define __VDP_BITMAPS_H_

#include <stdio.h>
#include <mos_api.h>

typedef struct Bitmap_header {
    char id[5];
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
} Bitmap_header;

typedef enum {
    SUCCESS,
    BAD_FILE,
    MALLOC_FAIL,
    NOT_IMAGE,
    WRONG_BPP
} BITMAP_LOAD_RESULT;

typedef enum {
    RGBA8888,
    RGBA2222,
    MONO
} BITMAP_FORMAT;

void vdp_assign_buffer_to_bitmap(uint16_t buffer_id, BITMAP_FORMAT bitmap_format, uint16_t width, uint16_t height);

/**
 * @brief Loads a bitmap image into a VDP buffer.
 * 
 * The image must be converted into an RGBA2222 format image using the
 * conversion tool first.
 * 
 * @param buffer_id 
 * @param filename 
 * @param header_data 
 * @return BITMAP_LOAD_RESULT 
 */
BITMAP_LOAD_RESULT load_bitmap_into_buffer(uint16_t buffer_id, char *filename, Bitmap_header *header_data);

void vdp_draw_current_bitmap(uint16_t x, uint16_t y);

/**
 * @brief Plots a VDP bitmap to the screen. Also selects the bitmap first.
 * 
 * @param buffer_id 
 * @param x 
 * @param y 
 */
void vdp_plot_bitmap(uint16_t buffer_id, int16_t x, int16_t y);

#endif