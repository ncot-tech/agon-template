#ifndef __VDP_UTILS_H_
#define __VDP_UTILS_H_

#include <agon/vdp_vdu.h>
#include <mos_api.h>
#include <stdint.h>

/**
 * @brief Writes a 16 bit value to the VDP
 * 
 * @param w The 16 bit value to write
 */
void write16bit(int16_t w);

/**
 * @brief VDU 23,0,C3 - Swap screen buffers
 * 
 * Only does something with double buffered screen modes.
 * See https://agonconsole8.github.io/agon-docs/vdp/Screen-Modes/
 * 
 */
void vdp_swap_screen_buffer();

/**
 * @brief Changes the current screen mode
 * 
 * See https://agonconsole8.github.io/agon-docs/vdp/Screen-Modes/
 * 
 * @param mode The mode number.
 */
void vdp_set_screen_mode(uint8_t mode);

/**
 * @brief Turn logical screen scaling on and off, where 1=on and 0=off.
 * 
 * VDU 23, 0, &C0, n
 * 
 * When logical scaling is turned off, the graphics system will no
 * longer use the 1280x1024 logical coordinate system and instead
 * use pixel coordinates. The screen origin point at 0,0 will change
 * to be the top left of the screen, and the Y axis will go down the
 * screen instead of up.
 * 
 * @param on 
 */
void vdp_enable_logical_screen_scaling(uint8_t on);

/**
 * @brief Set graphics origin
 * 
 * VDU 29, x; y;
 * 
 * @param x X Coordinate of new origin
 * @param y Y Coordinate of new origin
 */
void vdp_move_origin(int16_t x, int16_t y);

/**
 * @brief Changes graphics colour
 * 
 * This is just here for completeness, most drawing commands have a
 * colour parameter and will do this for you.
 * 
 * @param colour 
 */
void vdp_gcol(uint8_t colour);

void vdp_clg();

/**
 * @brief Changes the text colour
 * 
 * Colour numbers in the range 0-127 are interpreted as foreground colours,
 * and numbers in the range 128-255 are interpreted as background colours.
 * 
 * @param colour Colour number
 */
void vdp_colour(uint8_t colour);

#endif