# The Screen State Machine System

There is a state machine you can use for managing separate screens. It is defined in the screen/ folder
and consists of two files - screen.c and screen.h

An example of how they work is provided inside main_src/colour_bars.c

## State Machine Overview

The state machine contains an array called `screens` that consists of individual `Screen` structs.

Each struct has three function pointers

* init
* update
* draw

They are called appropriately by the state machine to make the current
screen work properly.

## Screen States

### Init

This is called once, and only once, when the screen is first instantiated.
Put inside it any code you need to call once.

This is a good place to set up the screen resolution using change_screen_mode().

### Update

This is your main update function. It gets called once a frame before the screen is drawn. Put your game logic in here.

If the screen returns -1, the screen will be run again next frame. If you return any other integer, it will be used as an ID to switch to next frame. Make sure the ID exists!

### Draw

Put any actual drawing code in here. This is where you might clear the screen, wait for vblank, swap buffers etc. None of that is done for you as it depends on the screen resolution and what you want to do.

You can put logic in here too, there is no real internal difference between update() and draw().

## Defining Screens

To define a screen you need to make a new C source and header file in the main_src/ directory. As a bare minimum it needs three functions that can be mapped to the init, update and draw functions above.

Then go into `main.c` and create a call to define_screen(), passing in the names of your three functions like this

`define_screen(colour_bars_init, colour_bars_update, colour_bars_draw);`

Don't forget to #include your screen's header file.

Screens are inserted into the state machine in the order they are defined, the first is screen ID zero and will run first.