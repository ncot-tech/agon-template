#ifndef __BMPRINT_H_
#define __BMPRINT_H_

#include <stdint.h>

/**
 * Bitmap font structure
 */
typedef struct Font {
    char *font_name;        /**< Name of the font */
    uint8_t char_count;     /**< Number of characters */
    uint8_t char_width;     /**< Width in pixels of a character */
    uint8_t char_height;    /**< Height in pixels of a character */
    uint16_t start_bitmap_id;   /**< Starting Agon VDP bitmap ID for the first character */
} Font;

/**
 * Prints a single character on the screen using the supplied font.
 * 
 * Uses VDP bitmaps to place a single character on the screen.
 * @param[in]   font    The font to use, see bm_load_font().
 * @param[in]   screenx The X position of the character.
 * @param[in]   screeny The Y position of the character.
 * @param[in]   c       The character to print. If not found in the font it will be subsituted by an error char.
 * 
 */
void bm_put_char(Font *font, int16_t screenx, int16_t screeny, char c);

/**
 * Loads a font definition off the SD card and turns it into a font structure used by the print routines.
 * 
 * After using the make_font.py tool use this function to load the resulting data file into your program.
 * You need to do this so the rest of these text printing routines will work.
 * 
 * Currently this function will make the program quit if it encounters loading errors since I wasn't sure how to
 * report errors in loading things to do with the text printing routines... If your game can't load an asset
 * it should probably quit.
 * 
 * @param[in]   font_def    The file generated by make_font.py
 * @param[out]  font        Pass in a pointer to where you want the definition storing, memory will be allocated.
 * @returns     Returns 0 on success, 1 on failure.
 * 
 */
uint8_t bm_load_font(char *font_def, Font *font);

/**
 * Draws a string of characters on the screen, spaced apart an appropriate amount.
 * 
 * This is equivalent to puts() in POSIX. Feed it a string, it'll print it.
 * Performs a rudimentary attempt at wrapping text at the screen edge.
 * 
 * @param[in]   font    The font definition created by bm_load_font().
 * @param[in]   screenx The X position of the first character.
 * @param[in]   screeny The Y position of the first character.
 * @param[in]   s       The NULL-terminated ASCII string to print.
 *
 */
void bm_put_string(Font *font, int16_t screenx, int16_t screeny, char *s);

/**
 * An implementation of printf() style text printing.
 * 
 * This is a basic implementation of printf(), it understands the following control characters
 * %c - Character
 * %d - Integer
 * %x - Hexadecimal
 * %s - String
 * 
 * Use it to print hexadecimal characters to your display, or to make nicely formatted score output, etc.
 * 
 * @param[in]   font    The font definition created by bm_load_font().
 * @param[in]   screenx The X position of the first character.
 * @param[in]   screeny The Y position of the first character.
 * @param[in]   format  The NULL-terminated printf() style format string.
 * @param[in]   varargs Pass in variables and other strings as appropriate.
 * 
 */
void bm_printf(Font *font, int16_t screenx, int16_t screeny, char *format, ...);
#endif
