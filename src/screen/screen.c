#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vdp/utils.h"

// Define a type for each screen
struct Screen {
    void (*init)(void);
    int (*update)(void);
    void (*draw)(void);
    // Add any other screen-specific functions or data here
};

// Define an array of screens
Screen *screens[MAX_SCREENS];
int num_screens = 0;
int current_screen_index = 0;

// Function to define screen
void define_screen(void (*init)(void), int (*update)(void), void (*draw)(void)) {
    // Check if there's still space in the array
    if (num_screens < MAX_SCREENS) {
        // Create the Screen struct
        Screen *new_screen = (Screen *)malloc(sizeof(Screen));
        if (new_screen != NULL) {
            new_screen->init = init;
            new_screen->update = update;
            new_screen->draw = draw;

            // Add the new screen to the array
            screens[num_screens++] = new_screen;
        }
    }
}

void set_current_screen(int screen_id)
{
    current_screen_index = screen_id;
}

// Function to execute the next screen based on the current screen's update function
void run_screens() {
    static bool first_run = true;
    // Get the current screen
    Screen *current_screen = screens[current_screen_index];
    if (current_screen == NULL || current_screen->update == NULL) {
        return; // Invalid current screen
    }

    if (first_run) {
        first_run = false;
        // Call the init function if needed
        if (current_screen->init != NULL) {
            current_screen->init();
        }
    }

    // Call the update function to determine the next screen
    int next_screen_id = current_screen->update();
    current_screen->draw();
    if (next_screen_id != -1 && next_screen_id < num_screens && next_screen_id != current_screen_index) {
        // Only update the screen index if it's different from the current one
        current_screen_index = next_screen_id;
        current_screen = screens[current_screen_index];
        
        // Call the init function if needed
        if (current_screen->init != NULL) {
            current_screen->init();
        }
    }    
}

void change_screen_mode(uint8_t mode, uint8_t enable_cursor, uint8_t logical_screen)
{
    vdp_set_screen_mode(mode);
    vdp_enable_logical_screen_scaling( logical_screen );
    vdp_cursor_enable( enable_cursor );
    vdp_clear_screen();
}