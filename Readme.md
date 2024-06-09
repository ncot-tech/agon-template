# Agon Light 2 C Template

This is a very much work in progress collection of stuff to aid with the [Agon Light C Compiler](https://ncot.uk/agon-light-c-development/) that runs under Linux and so on. It is likely to get updated randomly as I do further development and decide things need to be in here.

You'll need the "AGDev" C compiler already installed and working before this will be any use.

The "Tools" folder contains useful utilities, but they're designed for me and come with no documentation!

## What to do next

1. Clone this repo and strip out all the Git stuff from it, you'll want to make a new Git repo for whatever you're working on.
2. Look at the Makefile and edit as needed - mostly to set paths and so on, and to see what it does
3. Your code goes in "src/", data can go in "data/"
4. There is a symlink in data that needs to point to the SD card location of the Agon emulator

## When programming

* Running "make" will compile things
* Running "make emulate" will also copy the relevant code into the fake SD card and start the emulator, you will need to copy any resources yourself. It will also edit/create an autoexe.txt file in the fake SD card folder so your code starts immediately. Copy the autoexec.txt first if you've customised it.
