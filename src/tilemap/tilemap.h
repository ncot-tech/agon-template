#ifndef __Tilemap_H_
#define __Tilemap_H_

#include <mos_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A structure that represents a loaded Tilemap.
 */
typedef struct Tilemap {
    uint16_t map_width;         /**< The width of the map in tiles */
    uint16_t map_height;        /**< The height of the map in tiles */
    uint8_t tile_width;         /**< The width of a tile in pixels */
    uint8_t tile_height;        /**< The height of a tile in pixels */
    uint16_t bitmap_start_id;   /**< The 16 bit ID of the first tile in the Agon's VDP */
    uint16_t tile_count;        /**< How many unique tiles are in the tileset */
    uint16_t *map_data;         /**< An array of all the tile data, map_width * map_height in size */
} Tilemap;

/**
 * Loads a tilemap into memory.
 * 
 * Tilemaps must be created using Tiled and converted with the `make_tilemap.py` tool first.
 * 
 * @param[in] map_def The filename of the map to load. Must be an NCOTM format file.
 * @param[in] map The Tilemap struct to store the loaded map. Declare it yourself.
 */
void tilemap_load(char *map_def, Tilemap *map);
/**
 * Draws a tilemap on the screen.
 * 
 * For now it assumes all tilemaps are one screen tall. They can be wider.
 * 
 * @param[in] map The tilemap data to use
 * @param[in] x_start The starting tile column
 */
void tilemap_draw(Tilemap *map, uint16_t x_start);

uint16_t tilemap_get_tileid(Tilemap *map, uint16_t screen_x, uint16_t screen_y, uint8_t scroll_amount, uint16_t x_start);
#endif
