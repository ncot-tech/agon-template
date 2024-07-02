#include "error.h"
#include <agon/vdp_key.h>
#include <mos_api.h>
#include <stdio.h>
#include "vdp/utils.h"
#include "vdp/graphics.h"
#include "screen/screen.h"
#include <string.h>
#include "sprites/spritedef.h"

extern volatile SYSVAR *sv;

void raise_fatal_error(char *title, char *details)
{
    change_screen_mode(0, 1, 1);
    vdp_colour(134);
    vdp_clear_screen();
    
    vdp_colour(1);
    printf("--== [E R R O R !] ==--\n");
    printf("=======================\n");
    vdp_colour(0);
    printf("Shit's hit the fan, the program has stopped.\n\n");
    printf("%c%c%s\n", 17, 14, title);
    for (int i = 0; i < strlen(title); i++)
        putch('=');
    putch('\n');putch('\r');
    printf("%c%c%s\n", 17, 3, details);

    while(1) {} // Bye!

}