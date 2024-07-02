#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

#include <stdint.h>
#include "../maths/point.h"

/**
 * @brief Draws a line between two points using the VDP
 * 
 * @param origin_x Absolute start X position
 * @param origin_y Absolute start Y position
 * @param end_x Absolute end X position
 * @param end_y Absolute end Y position
 * @param colour Colour ID
 */
void vdp_draw_line(int16_t origin_x, int16_t origin_y, int16_t end_x, int16_t end_y, uint8_t colour);

/**
 * @brief Plots a point on the screen using the VDP
 * 
 * @param x 
 * @param y 
 * @param colour 
 */
void vdp_plot_point(uint16_t x, uint16_t y, uint8_t colour);
void vdp_plot_circle(uint16_t x, uint16_t y, uint16_t diameter, uint8_t colour);
void vdp_draw_triangle(Point p1, Point p2, Point p3, uint8_t colour);
void vdp_plot_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t colour);

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
