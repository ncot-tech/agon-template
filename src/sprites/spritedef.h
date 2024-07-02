#ifndef __SPRITEDEF_H_
#define __SPRITEDEF_H_

#include <stdint.h>
#include "../maths/point.h"

typedef struct SpriteFrame {
    uint16_t frame;
    uint16_t duration;
} SpriteFrame;

typedef struct SpriteAnimationDef {
    uint16_t length;
    SpriteFrame *frames;
} SpriteAnimationDef;

typedef struct SpriteDef {
    uint16_t sprite_width;
    uint16_t sprite_height;
    uint16_t sprite_count;
    uint16_t state_count;
    SpriteAnimationDef *state_frames;
} SpriteDef;

void debug_print_spritedef(SpriteDef *sprite_def);
void spritedef_init(uint16_t start_bitmap_id);
uint16_t spritedef_load(char *sprite_file);
SpriteDef *spritedef_get(uint16_t sprite_def_id);
void spritedef_draw_frame(SpriteDef *sprite_def, uint16_t state, uint16_t frame, Point position);

#endif