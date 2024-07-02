#include "tilemap.h"
#include <stdarg.h>
#include <string.h>
#include "../maths/xitoa.h"
#include "../vdp/bitmaps.h"
#include "../vdp/graphics.h"

void tilemap_load(char *map_def, Tilemap *map)
{
    uint8_t file = mos_fopen(map_def, 0x01);
    if (!file) {
        printf ("Can't open file >%s<\n", map_def);
        exit(1);
    }

    char file_tag[5];
    mos_fread(file, (char *)file_tag, 5);
    if (file_tag[0] != 'N' || file_tag[1] != 'C' || file_tag[2] != 'O'
	    || file_tag[3] != 'T' || file_tag[4] != 'M') {
        printf ("Not a map %c%c%c%c%c\n", file_tag[0], file_tag[1], file_tag[2],
                file_tag[3], file_tag[4]);
        exit(1);
    }

    mos_fread(file, (char *)map, 10);

    printf ("Read map header\n  width:%d\n  height:%d\n  tile width:%d\n  tile_height:%d\n",
            map->map_width, map->map_height, map->tile_width, map->tile_height);
    printf ("There are %d tiles, bitmaps start with ID %d\n",
            map->tile_count, map->bitmap_start_id);

    // Load each tile into the VDP
    for (int i = 0; i < map->tile_count; i++) {
        uint16_t tile_id = 0;
        mos_fread(file, (char *)&tile_id, 2);
        uint16_t filename_len = 0;
        mos_fread(file, (char *)&filename_len, 2);
        char *filename = (char *)malloc(sizeof(char) * filename_len+1);
        mos_fread(file, (char *)filename, filename_len);
        filename[filename_len] = '\0';  // Null terminate the string
        // remember to add map->bitmap_start_id to the tile ID when loading into VDP
        // read it into the VDP here
        Bitmap_header header;
        BITMAP_LOAD_RESULT res = load_bitmap_into_buffer(map->bitmap_start_id+tile_id,
            filename, &header);
        if (res != SUCCESS) {
            printf ("Failed to load %s\n", filename);
            exit(1);
            return;
        }
        vdp_assign_buffer_to_bitmap(map->bitmap_start_id+tile_id,RGBA2222,header.width,header.height);
        vdp_plot_bitmap(map->bitmap_start_id+tile_id, 0,map->tile_height);
    }

    // Now allocate RAM for the tilemap itself
    map->map_data = (uint16_t *)malloc(sizeof(uint16_t) * map->map_width * map->map_height);

    // And read that in
    mos_fread(file, (char *)map->map_data, sizeof(uint16_t) * map->map_width * map->map_height);
}

// For now only allow drawing from a starting x position, not a y position too.
// For now assuming all maps are one screen tall
void tilemap_draw(Tilemap *map, uint16_t x_start)
{
    int tw4 = map->tile_width*4;
    int th4 = map->tile_height*4.3;
    
    for (int y = 0; y < map->map_height ; y++) {
        for (int x = 0; x < 20; x++) {
            vdp_plot_bitmap(map->bitmap_start_id+map->map_data[x_start + x + y * map->map_width],
                (x*tw4),
                (y*th4));
        }
    }
}

uint16_t tilemap_get_tileid(Tilemap *map, uint16_t screen_x, uint16_t screen_y, uint8_t scroll_amount, uint16_t x_start)
{
    uint16_t tx = (screen_x+scroll_amount) / 64;
    uint16_t ty = screen_y / 64;
    
    return map->map_data[x_start + tx + ty * map->map_width];
}
