#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <stdint.h>

extern uint8_t current_keystates[];
extern uint8_t previous_keystates[];
extern volatile uint8_t *keymap;

#define RAW_KEY_UP (*(keymap+7) & 0x02)
#define RAW_KEY_DOWN (*(keymap+5) & 0x02)
#define RAW_KEY_LEFT (*(keymap+3) & 0x02)
#define RAW_KEY_RIGHT (*(keymap+15) & 0x02)

#define RAW_KEY_SPACE (*(keymap+12) & 0x04)
#define RAW_KEY_W (*(keymap+4) & 0x02)
#define RAW_KEY_S (*(keymap+10) & 0x02)
#define RAW_KEY_A (*(keymap+8) & 0x02)
#define RAW_KEY_D (*(keymap+6) & 0x04)

#define RAW_KEY_LCTRL (*keymap & 0x10)
#define RAW_KEY_LALT (*keymap & 0x20)
#define RAW_KEY_LSHIFT (*keymap & 0x08)
#define RAW_KEY_RSHIFT (*keymap & 0x40)
#define RAW_KEY_RCTRL (*keymap & 0x80)
#define RAW_KEY_RALT (*(keymap+1) & 0x01)

#define RAW_KEY_ESC (*(keymap+14) & 0x01)
#define RAW_KEY_Z (*(keymap+12) & 0x02)
#define RAW_KEY_X (*(keymap+8) & 0x04)
#define RAW_KEY_C (*(keymap+10) & 0x04)

#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_SPACE 4
#define KEY_W 5
#define KEY_S 6
#define KEY_A 7

#define KEY_D 10
#define KEY_LCTRL 11
#define KEY_LALT 12
#define KEY_LSHIFT 13
#define KEY_RSHIFT 14
#define KEY_RCTRL 15
#define KEY_RALT 16
#define KEY_ESC 17

#define KEY_Z 21
#define KEY_X 22
#define KEY_C 23

#define TOGGLE_BIT(dest, source, bit_pos) (dest = (dest & ~(1 << (bit_pos))) | (!!source << (bit_pos)))
#define BIT_CHECK(b,bit_pos) ((b) &   (1<<(bit_pos)))
#define IS_KEY_HELD(keycode) (BIT_CHECK(current_keystates[(keycode) / 10], (keycode) % 10))
#define WAS_KEY_HELD(keycode) (BIT_CHECK(previous_keystates[(keycode) / 10], (keycode) % 10))
#define IS_KEY_PRESSED(keycode) (IS_KEY_HELD(keycode) && !WAS_KEY_HELD(keycode))

void update_keys();
void init_keys();

#endif
