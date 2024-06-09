#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

//#include "globals.h"
#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>



typedef struct ncotb_header {
    char id[5];
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
} ncotb_header;

typedef enum {
    SUCCESS,
    BAD_FILE,
    MALLOC_FAIL,
    NOT_IMAGE,
    WRONG_BPP
} bitmap_load_result;

typedef enum {
    RGBA8888,
    RGBA2222,
    MONO
} BITMAP_FORMAT;

typedef struct Point {
    int16_t x;
    int16_t y;
} Point;


void flip_buffer();
void set_video_mode(uint8_t mode);
void draw_line(int16_t origin_x, int16_t origin_y, int16_t end_x,
      int16_t end_y, uint8_t colour);
void gcol(uint8_t colour);
void plot_point(uint16_t x, uint16_t y, uint8_t colour);
void plot_circle(uint16_t x, uint16_t y, uint16_t diameter, uint8_t colour);
void draw_triangle(Point p1, Point p2, Point p3, uint8_t colour);
void switch_logical(bool on);
bitmap_load_result load_bitmap_into_buffer(uint16_t buffer_id, char *filename, ncotb_header *header_data);
void write16bit(int16_t w);
void vdp_move_origin(int16_t x, int16_t y);
void vdp_plot_rect(uint8_t colour, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void clear_buffer(uint16_t buffer_id);
void select_buffer(uint24_t buffer_id);
void add_stream_to_buffer(uint16_t buffer_id, char *buffer_content,
              uint16_t buffer_size);

void vdp_extended_select(uint16_t buffer_id);
void vdp_draw(uint16_t x, uint16_t y);
void consolidate_buffer(uint16_t buffer_id);
void split_into_from(uint16_t buffer_id, uint16_t into, uint16_t from);
void split_into_cols_from(uint16_t buffer_id, uint16_t width, uint16_t cols,
              uint16_t from);
void assign_buffer_to_bitmap(uint16_t buffer_id, BITMAP_FORMAT bitmap_format,
                 uint16_t width, uint16_t height);
void vdp_plot_bitmap(uint16_t buffer_id, int16_t x, int16_t y);
#endif
