# pico_atlast 

Documentation: http://www.fourmilab.ch/atlast/ and https://www.forth.com/starting-forth/ and https://www.dnd.utwente.nl/~tim/colorforth/Leo-Brodie/thinking-forth.pdf

Atlast Forth for Raspberry Pi Pico is a forth programming environment for the pico. 

Put the forth code in the file forth.h and compile atlast.c in the cmake environment, see https://github.com/raspberrypi/pico-sdk

Use the Makefile included in this repo to compile atlast.c to run on a Raspberry Pi or other host to be able to test your forth code before flashing to the pico. The forth code must contain an infinite loop, e.g. begin ... again to keep the application running.

At this date january 30 only a few pico primitives are implemented, more to come.
