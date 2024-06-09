#ifndef __BMPRINT_H_
#define __BMPRINT_H_

#include <mos_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct font {
    char *font_name;
    uint8_t char_count;
    uint8_t char_width;
    uint8_t char_height;
    uint16_t start_bitmap_id;
} font;

void bm_put_char(font *font, int16_t screenx, int16_t screeny, char c);
uint8_t bm_load_font(char *font_def, font *font);
void bm_put_string(font *font, int16_t screenx, int16_t screeny, char *s);
void bm_printf(font *font, int16_t screenx, int16_t screeny, char *format, ...);
#endif
