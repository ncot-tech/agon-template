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
void debug_print_bitmap(Bitmap_header *header);
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
BITMAP_LOAD_RESULT load_bitmap_into_buffer_fp(uint16_t buffer_id, uint8_t file, Bitmap_header *header_data);



#endif