# pico_atlast 

Documentation: https://elinux.org/Forth

Atlast Forth for Raspberry Pi Pico is a forth programming environment for the pico. 

Put the forth code in the file forth.h and compile atlast.c in the cmake environment, see https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf

Use the Makefile included in this repo to compile atlast.c to run on the Raspberry Pi or other host to be able to test your forth code before flashing to the pico. The forth code must contain an indefinite loop, e.g. begin ... again to keep the application running.

At this date january 30 only a few primitives are implemented, more to come.
