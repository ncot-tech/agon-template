#include "bmprint.h"
#include <stdarg.h>
#include <string.h>
#include "xitoa.h"
#include "graphics.h"

void load_font_def(char *font_def, font *font)
{
    uint8_t file = mos_fopen(font_def, 0x01);
	if (!file) {
        printf ("Can't open file %s\n", font_def);
        exit(1);
	}

    char file_tag[5];
	mos_fread(file, (char *)file_tag, 5);
	if (file_tag[0] != 'N' || file_tag[1] != 'C' || file_tag[2] != 'O'
	    || file_tag[3] != 'T' || file_tag[4] != 'F') {
        printf ("Not a font %c%c%c%c%c\n", file_tag[0], file_tag[1], file_tag[2],
                file_tag[3], file_tag[4]);
        exit(1);
	}

    uint16_t name_length = 0;
    mos_fread(file, (char *)&name_length, 2);

    printf ("Name is %d long\n", name_length);

    font->font_name = (char *)malloc(sizeof(char) * name_length + 1);
    mos_fread(file, font->font_name, name_length);
    font->font_name[name_length] = 0;   // Null terminate it

    printf ("Font name is %s\n", font->font_name);

    mos_fread(file, (char *)&font->char_count, 5);   // Read count, width, height, bitmap_id

    printf ("Read %s which is %dx%d and contains %d chars, starting at ID %d\n",
            font->font_name, font->char_width, font->char_height, font->char_count, font->start_bitmap_id);
}

uint8_t bm_load_font(char *font_def, font *font)
{
    load_font_def(font_def, font);

    bitmap_load_result res;

    ncotb_header image_header;
    
    // Cut up the font_def to remove the .fon and then replace with
    // the 3 digit count and .222
    uint16_t path_length = strlen(font_def) + 4;
    char *dot = strrchr(font_def, '.');
    size_t basename_length = dot - font_def;
    char *basename = (char *)malloc(sizeof(char) * basename_length);
    strncpy(basename, font_def, basename_length);
    char *fontname = (char *)malloc(sizeof(char) * path_length);

	for (int i = 0; i < font->char_count; i++) {
		snprintf(fontname, path_length, "%s_%03d.222", basename, i);
        printf ("Loading %s\n", fontname);
		res = load_bitmap_into_buffer(font->start_bitmap_id + i, fontname, &image_header);
		if (res != SUCCESS) {
			printf ("Failed to load %s\n", fontname);
			return 1;
		}
		assign_buffer_to_bitmap(font->start_bitmap_id + i,RGBA2222,image_header.width,image_header.height);
                vdp_plot_bitmap(font->start_bitmap_id + i, 0,image_header.height);
	}

    return 0;
}

void bm_put_char(font *font, int16_t screenx, int16_t screeny, char c)
{
    int id = ((c-32) <= 58) ? (c-32) : 10;
    vdp_plot_bitmap(font->start_bitmap_id + id, screenx, screeny);
}

void bm_put_string(font *font, int16_t screenx, int16_t screeny, char *s)
{
    char *currentChar = s;
    int xpos = 0;
    int ypos = 0;
    uint16_t id = 10;   // Default character is a * for "can't draw that"
    while (*currentChar) {
        if ((*currentChar)-32 <= 58)    // Char within range?
            id = (*currentChar)-32;    // Calculate the ID
        vdp_plot_bitmap(font->start_bitmap_id + id, screenx+(xpos*8), screeny+(ypos*8));
        currentChar++;
        xpos++;
        if (xpos >= 320) {
            xpos = 0;
            ypos += 8;
        }
    }
}

void bm_printf(font *font, int16_t screenx, int16_t screeny, char *format, ...)
{
    char tmpStr[33];
    int xpos = 0;
    int ypos = 0;
    uint16_t id = 10;   // Default * for "can't print this"
    va_list argp;
    va_start(argp, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case '%': tmpStr[0] = '%'; tmpStr[1] = 0; break;
                case 'c': tmpStr[0] = va_arg(argp, int); tmpStr[1] = 0; break;
                case 'd': xitoa(va_arg(argp, int), tmpStr, 10); break;
                case 'x': xitoa(va_arg(argp, int), tmpStr, 16); break;
                case 's': strncpy(tmpStr, va_arg(argp, char*), 32); tmpStr[32] = 0; break;
                default : tmpStr[0] = '?';tmpStr[1] = 0; break;
            }
            bm_put_string(font, screenx+(xpos*8), screeny+(ypos*8), tmpStr);
            xpos += strlen(tmpStr) - 1;
            if (xpos >= 320) {
                ypos += 8;
                xpos = 0;
            }
        } else {
            if ((*format)-32 <= 58)    // Char within range?
                id = (*format)-32;    // Calculate the ID
            else
                id = 10;    // Draw a * instead
            vdp_plot_bitmap(font->start_bitmap_id + id, screenx+(xpos*8), screeny+(ypos*8));
        }
        format++;
        xpos+=4;
        if (xpos >= 320) {
            xpos = 0;
            ypos += 8;
        }

    }
    va_end(argp);

  //  
}

