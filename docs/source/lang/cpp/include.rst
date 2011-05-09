.. highlight:: cpp

.. _lang-include:

``#include``
============

``#include`` is used to include outside libraries in your sketch.
This gives the programmer access to a large group of standard C
libraries (groups of pre-made functions and data types), and also
libraries written especially for Maple.

Example
-------

This example (from the `Arduino LiquidCrystal Tutorial
<http://arduino.cc/en/Tutorial/LiquidCrystal>`_) includes a library
that is used to control :ref:`LCD displays
<libraries-liquid-crystal>`::

    // include the library code:
    #include <LiquidCrystal.h>

    // initialize the library with the numbers of the interface pins
    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

    void setup() {
      // set up the LCD's number of columns and rows:
      lcd.begin(16, 2);
      // Print a message to the LCD.
      lcd.print("hello, world!");
    }

    void loop() {
      // set the cursor to column 0, line 1
      // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 1);
      // print the number of seconds since reset:
      lcd.print(millis()/1000);
    }

Note that a ``#include`` line, like :ref:`#define <lang-define>`,
has **no semicolon**.  The compiler will print strange error messages
if you add one.

C Standard Library
------------------

The standard C library that comes with Maple is called `newlib
<http://sourceware.org/newlib/>`_.  Its main sources of documentation
are its `main reference <http://sourceware.org/newlib/libc.html>`_
page and its `math functions
<http://sourceware.org/newlib/libm.html>`_ reference page.  Here's an
example that imports the math.h library in order to take the `cube
root <http://en.wikipedia.org/wiki/Cube_root>`_ of a number::

    #include <math.h>

    void setup() {
        // no setup necessary
    }

    void loop() {
        // "cbrt" stands for "cube root"
        double cubeRootOf3 = cbrt(3.0);
        // prints a number that is approximately the cube root of 3:
        SerialUSB.println(cubeRootOf3);
    }

.. include:: /arduino-cc-attribution.txt
