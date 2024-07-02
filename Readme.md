# Agon Light 2 C Template
**Version: 0.2.0
James Grimwood / james@ncot.uk / https://ncot.uk

This is a very much work in progress collection of stuff to aid with the [Agon Light C Compiler](https://ncot.uk/agon-light-c-development/) that runs under Linux and so on. It is likely to get updated randomly as I do further development and decide things need to be in here.

It uses [Semantic Versioning](https://semver.org/spec/v2.0.0.html)

## Requirements

* You'll need the [AGDev](https://github.com/pcawte/AgDev) C compiler already installed and working before this will be any use.
* The [fab-agon](https://github.com/tomm/fab-agon-emulator) emulator will also be useful.
* The "Tools" folder contains useful utilities.
* Doxygen generated documentation can be generated, and exists in the docs/doxygen folder.

## What to do next

1. Clone this repo and strip out all the Git stuff from it, you'll want to make a new Git repo for whatever you're working on.
2. Look at the Makefile and edit as needed - mostly to set paths and so on, and to see what it does
3. Your code goes in "src/main_src", data can go in "data/"
4. You will need to edit main.c, see the comments in there
5. Look at the documentation inside `docs/` if you point a browser at `docs/doxygen/html/index.html` you can read it all.

I am working on a wizard type tool to copy and set up a new project from this to reduce the amount of effort.

## When programming

* Running `make` will compile things, this should work out the box if you set it up correctly and is a good test.
* Running `make emulate` will also copy the relevant code into the fake SD card and start the emulator, you will need to copy any resources yourself. It will also edit/create an autoexe.txt file in the fake SD card folder so your code starts immediately. Copy the autoexec.txt first if you've customised it.
* Running `make inst_sd` will copy everything onto the SD card if you mounted it properly.

If something doesn't make sense, raise an issue. I hate poorly documented code and am putting in effort to make this code have better than average documentation!
I've learnt that if I document it, I can also read the docs and don't need to remember what everything does! Fancy that... documentation can be useful. Spread the word ;-)