#include <stdlib.h>
#include "spritedef.h"
#include "../vdp/bitmaps.h"
#include "../error.h"
#include "../debug/debug.h"
#include "../vdp/graphics.h"

#define MAX_SPRITEDEFS 100
SpriteDef sprite_defs[MAX_SPRITEDEFS];
uint16_t sprite_def_count;
uint16_t current_bitmap_id;

void spritedef_init(uint16_t start_bitmap_id)
{
    sprite_def_count = 0;
    current_bitmap_id = start_bitmap_id;
}

uint16_t spritedef_load(char *sprite_file)
{
    uint8_t file = mos_fopen(sprite_file, 0x01);
    if (!file) {
        printf ("Can't open file >%s<\n", sprite_file);
        exit(1);
    }

    char file_tag[5];
    mos_fread(file, (char *)file_tag, 5);
    if (file_tag[0] != 'N' || file_tag[1] != 'C' || file_tag[2] != 'O'
	    || file_tag[3] != 'T' || file_tag[4] != 'S') {
        printf ("Not a sprite %c%c%c%c%c\n", file_tag[0], file_tag[1], file_tag[2],
                file_tag[3], file_tag[4]);
        exit(1);
    }

    mos_fread(file, (char *)&sprite_defs[sprite_def_count], 8);

    debug_printf ("Read sprite header\n  width:%d\n  height:%d\n  state count:%d\n  sprite count:%d\n",
            sprite_defs[sprite_def_count].sprite_width, sprite_defs[sprite_def_count].sprite_height,
            sprite_defs[sprite_def_count].state_count, sprite_defs[sprite_def_count].sprite_count);

    sprite_defs[sprite_def_count].state_frames = (SpriteAnimationDef *)malloc(sizeof(SpriteAnimationDef) *
        sprite_defs[sprite_def_count].state_count);
    // Now read each state
    for (int i = 0; i < sprite_defs[sprite_def_count].state_count; i++) {
        debug_printf("Processing state frames %d\n", i);
        SpriteAnimationDef* anim_def = &(sprite_defs[sprite_def_count].state_frames[i]);
        debug_printf ("Anim def at %x\n", anim_def);
        mos_fread(file, (char *)&anim_def->length, 2);
        debug_printf ("There are %d frames in this state\n", anim_def->length);
        anim_def->frames = (SpriteFrame *)malloc(sizeof(SpriteFrame) * anim_def->length);
        mos_fread(file, (char *)anim_def->frames, sizeof(SpriteFrame) * anim_def->length);

        /* Because of how data is stored in the original json file, there is a direct relationship
         * between the frame number and the order of the bitmaps.
         * If we add the current bitmap ID to this, we can work out what VDP bitmap will be assigned
         * later on
         */

        // TODO: THIS IS NOW BROKEN, I HAVE ADDED DURATION TO THE FRAMES AND MADE A NEW STRUCT.
        for (int j = 0; j < anim_def->length; j++) {
            anim_def->frames[j].frame += current_bitmap_id;
            debug_printf ("Frame %d ", anim_def->frames[j].frame);
            debug_printf ("Duration %d ", anim_def->frames[j].duration);
        }
        debug_printf("\n");
    }

    // Now read the bitmaps
    debug_printf ("Reading bitmap data\n");
    Bitmap_header header_data;
    for (int i = 0; i < sprite_defs[sprite_def_count].sprite_count; i++) {
        /* Because of the above explanation, each bitmap we load directly relates to the animation
         * frames, so we can increment the current bitmap id to match
         */
        if (load_bitmap_into_buffer_fp(current_bitmap_id, file, &header_data) == SUCCESS) {
            vdp_assign_buffer_to_bitmap(current_bitmap_id, RGBA2222,header_data.width,header_data.height);
            debug_printf("Bitmap id %d\n", current_bitmap_id);
            debug_print_bitmap(&header_data);
            current_bitmap_id++;
        }
    }

    debug_print_spritedef(&sprite_defs[sprite_def_count]);

    sprite_def_count++;
    if (sprite_def_count >= MAX_SPRITEDEFS)
        raise_fatal_error("Too many spritedefs", "Tried to load too many sprite defs!");

    return sprite_def_count-1;  // Return the sprite def ID we just made
}

SpriteDef *spritedef_get(uint16_t sprite_def_id)
{
    debug_printf("Returning spritedef %d\n", sprite_def_id);
    if (sprite_def_id < sprite_def_count)
        return &(sprite_defs[sprite_def_id]);
    else
        return 0;
}

void debug_print_spritedef(SpriteDef *sprite_def)
{
    debug_printf("SpriteDef\n"
                 "    width %d\n"
                 "    height %d\n"
                 "    sprite count %d\n"
                 "    state count %d\n",
                 sprite_def->sprite_width,
                 sprite_def->sprite_height,
                 sprite_def->sprite_count,
                 sprite_def->state_count);
    for (int i = 0; i < sprite_def->state_count; i++) {
        debug_printf("    Animation Def\n"
                     "        length %d\n",
                     sprite_def->state_frames[i].length);
        for (int j = 0; j < sprite_def->state_frames[i].length; j++) {
            debug_printf("        Frame %d",
                         sprite_def->state_frames[i].frames[j]);
        }
        debug_printf("\n");
    }
}

void spritedef_draw_frame(SpriteDef *sprite_def, uint16_t state, uint16_t frame, Point position)
{
    debug_printf("drawing frame for state %d, frame %d", state, frame);
    uint16_t sprite_id = sprite_def->state_frames[state].frames[frame].frame;
    debug_printf("Drawing vdp bitmap %d at %d,%d\n",sprite_id, position.x, position.y);
    vdp_plot_bitmap(sprite_id, position.x, position.y);
}