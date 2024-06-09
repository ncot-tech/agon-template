#include "keyboard.h"
#include <agon/vdp_key.h>
#include <mos_api.h>

volatile uint8_t *keymap;

uint8_t previous_keystates[3];
uint8_t current_keystates[3];

void init_keys()
{
    keymap = mos_getkbmap();
    update_keys();
}

void update_keys()
{
	previous_keystates[0] = current_keystates[0];
	previous_keystates[1] = current_keystates[1];
	previous_keystates[2] = current_keystates[2];

	// Update the current keystates
	TOGGLE_BIT(current_keystates[0], RAW_KEY_UP, KEY_UP);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_DOWN, KEY_DOWN);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_LEFT, KEY_LEFT);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_RIGHT, KEY_RIGHT);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_SPACE, KEY_SPACE);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_W, KEY_W);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_S, KEY_S);
	TOGGLE_BIT(current_keystates[0], RAW_KEY_A, KEY_A);

	TOGGLE_BIT(current_keystates[1], RAW_KEY_D, KEY_D - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_LCTRL, KEY_LCTRL - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_LALT, KEY_LALT - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_LSHIFT, KEY_LSHIFT - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_RSHIFT, KEY_RSHIFT - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_RCTRL, KEY_RCTRL - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_RALT, KEY_RALT - 10);
	TOGGLE_BIT(current_keystates[1], RAW_KEY_ESC, KEY_ESC - 10);

	TOGGLE_BIT(current_keystates[2], RAW_KEY_Z, KEY_Z - 20);
	TOGGLE_BIT(current_keystates[2], RAW_KEY_X, KEY_X - 20);
	TOGGLE_BIT(current_keystates[2], RAW_KEY_C, KEY_C - 20);
}


