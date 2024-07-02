#ifndef __SPRITE_H_
#define __SPRITE_H_

#include "spritedef.h"
#include "../maths/rect.h"
#include "../maths/point.h"

typedef enum {
    PAUSED,
    FORWARD,
    REVERSE
} SPRITE_ANIMATION_STATE;

typedef enum {
    INACTIVE,
    ACTIVE
} SPRITE_ACTIVE_STATE;

typedef enum {
    INVISIBLE,
    VISIBLE
} SPRITE_VISIBLE_STATE;

typedef struct Sprite Sprite;
typedef void (*CollisionFuncPtr)(Sprite *this, Sprite *other);
typedef void (*UpdateFuncPtr)(Sprite *this);

/* TODO

Rename these to better names.

A sprite is made up from different
    Behaviours - idle, running, etc
    Animations - the visual representation of a behaviour
        Which is made up from frames - the individual graphics we see on the screen
    Render state - visible / invisible
    Activation state - active / inactive
*/

typedef struct Sprite {
    uint16_t id;
    SpriteDef *sprite_def;
    Point position;
    uint32_t animation_timer;
    uint8_t current_animation_state;
    uint16_t current_animation_frame;
    SPRITE_ANIMATION_STATE animation_state;
    SPRITE_ACTIVE_STATE sprite_active_state;
    SPRITE_VISIBLE_STATE sprite_visible_state;
    Rect collision_rect;
    CollisionFuncPtr collision_func;
    UpdateFuncPtr update_func;
    void *user_data;
} Sprite;

void debug_print_sprite(Sprite *sprite);
void sprite_system_init();
uint16_t sprite_instantiate(uint16_t sprite_def_id, Point position);
void sprite_system_update();
void sprite_system_draw();
void sprite_activate(uint16_t sprite_id, SPRITE_ACTIVE_STATE active_state);
void sprite_set_animation_state(uint16_t sprite_id, SPRITE_ANIMATION_STATE animation_state);
void sprite_set_visible(uint16_t sprite_id, SPRITE_VISIBLE_STATE visible_state);
void sprite_set_state(uint16_t sprite_id, uint8_t sprite_state);
#endif