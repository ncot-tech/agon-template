#ifndef SCREEN_H
#define SCREEN_H

#include <mos_api.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024

// Forward declaration of Screen struct
struct Screen;

// Define a type for each screen
typedef struct Screen Screen;
#define MAX_SCREENS 10

// Function prototypes for screen-related functions
void set_current_screen(int screen_id);
void define_screen(void (*init)(void), int (*update)(void), void (*draw)(void)); 
void run_screens(void);
void change_screen_mode(uint8_t mode, uint8_t enable_cursor, uint8_t logical_screen);
#endif /* SCREEN_H */

