.. _arduino-include:

#include
========

**#include** is used to include outside libraries in your sketch.
This gives the programmer access to a large group of standard C
libraries (groups of pre-made functions), and also libraries
written especially for Arduino.



The main reference page for AVR C libraries (AVR is a reference to
the Atmel chips on which the Arduino is based) is
`here. <http://www.nongnu.org/avr-libc/user-manual/modules.html>`_



Note that **#include**, similar to **#define**, has no semicolon
terminator, and the compiler will yield cryptic error messages if
you add one.



Example
-------

This example includes a library that is used to put data into the
program space *flash* instead of *ram*. This saves the ram space
for dynamic memory needs and makes large lookup tables more
practical.



::

    #include <avr/pgmspace.h>
    
    prog_uint16_t myConstants[] PROGMEM = {0, 21140, 702  , 9128,  0, 25764, 8456,
    0,0,0,0,0,0,0,0,29810,8968,29762,29762,4500};


