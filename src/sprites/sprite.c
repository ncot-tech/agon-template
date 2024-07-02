#include "sprite.h"
#include "spritedef.h"
#include "../vdp/bitmaps.h"
#include "../debug/debug.h"
#include "../vdp/graphics.h"
#include "../global.h"

#define MAX_SPRITES 100

Sprite sprites[MAX_SPRITES];

void sprite_system_init()
{
    for (int x = 0; x < MAX_SPRITES; x++) {
        sprites[x].sprite_active_state = INACTIVE;
        sprites[x].collision_func = NULL;
        sprites[x].update_func = NULL;
        sprites[x].user_data = NULL;
    }
}

void sprite_activate(uint16_t sprite_id, SPRITE_ACTIVE_STATE active_state)
{
    sprites[sprite_id].sprite_active_state = active_state;
}

void sprite_set_animation_state(uint16_t sprite_id, SPRITE_ANIMATION_STATE animation_state)
{
    sprites[sprite_id].animation_state = animation_state;
}

void sprite_set_visible(uint16_t sprite_id, SPRITE_VISIBLE_STATE visible_state)
{
    sprites[sprite_id].sprite_visible_state = visible_state;
}

void sprite_set_state(uint16_t sprite_id, uint8_t sprite_state)
{
    sprites[sprite_id].current_animation_state = sprite_state;
    sprites[sprite_id].current_animation_frame = 0;
}

uint16_t sprite_instantiate(uint16_t sprite_def_id, Point position)
{
    debug_printf("Instantiating sprite %d at %d,%d\n", sprite_def_id, position.x, position.y);
    for (int x = 0; x < MAX_SPRITES; x++) {
        if (sprites[x].sprite_active_state == INACTIVE) {
            sprites[x].sprite_active_state = ACTIVE;
            sprites[x].id = x;
            sprites[x].sprite_def = spritedef_get(sprite_def_id);
            sprites[x].position = position;
            sprites[x].animation_timer = 0;
            sprites[x].current_animation_state = 0;
            sprites[x].current_animation_frame = 0;
            sprites[x].animation_state = PAUSED;
            sprites[x].sprite_visible_state = VISIBLE;
            sprites[x].collision_func = NULL;
            sprites[x].update_func = NULL;
            sprites[x].user_data = NULL;

            debug_print_sprite(&(sprites[x]));
            debug_print_spritedef(sprites[x].sprite_def);
            return x;
        }
    }

    return 0;
}

void debug_print_sprite(Sprite *sprite) {
    debug_printf("Sprite id %d\n"
                 "    active state %d\n"
                 "    position %d,%d\n"
                 "    current anim state %d\n"
                 "    current anim frame %d\n"
                 "    anim state %d\n"
                 "    visible state %d\n"
        , sprite->id, sprite->sprite_active_state, sprite->position.x, sprite->position.y,
        sprite->current_animation_state, sprite->current_animation_frame, sprite->animation_state,
        sprite->sprite_visible_state);
}

void sprite_system_update()
{
    for (int x = 0; x < MAX_SPRITES; x++) {
        if (sprites[x].sprite_active_state == ACTIVE) {
            // If there is an update func, run it
            if (sprites[x].update_func)
                sprites[x].update_func(&sprites[x]);

            // if the animation is playing forwards, increment
            if (sprites[x].animation_timer <= globals.sysvars->time) {
                // Yeah C gets a bit shit at times
                sprites[x].animation_timer = globals.sysvars->time + sprites[x].sprite_def->state_frames[sprites[x].current_animation_state].frames[sprites[x].current_animation_frame].duration;

                if (sprites[x].animation_state == FORWARD) {
                    sprites[x].current_animation_frame++;
                    // If we're at the last frame, reset to zero
                    if (sprites[x].current_animation_frame >=
                        sprites[x].sprite_def->state_frames[sprites[x].current_animation_state].length)
                        sprites[x].current_animation_frame = 0;
                }
            }
        }
    }
}

void sprite_system_draw()
{
    for (int x = 0; x < MAX_SPRITES; x++) {
        if (sprites[x].sprite_active_state == ACTIVE &&
            sprites[x].sprite_visible_state == VISIBLE) {
                spritedef_draw_frame(sprites[x].sprite_def, sprites[x].current_animation_state,
                    sprites[x].current_animation_frame, sprites[x].position);
        }
    }
}