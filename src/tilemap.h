#ifndef __TILEMAP_H_
#define __TILEMAP_H_

#include <mos_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tilemap {
    uint16_t map_width;
    uint16_t map_height;
    uint8_t tile_width;
    uint8_t tile_height;
    uint16_t bitmap_start_id;
    uint16_t tile_count;
    uint16_t *map_data;
} tilemap;

void tilemap_load(char *map_def, tilemap *map);
void tilemap_draw(tilemap *map, uint16_t x_start, uint8_t scroll_amount);
uint16_t tilemap_get_tileid(tilemap *map, uint16_t screen_x, uint16_t screen_y, uint8_t scroll_amount, uint16_t x_start);
#endif
