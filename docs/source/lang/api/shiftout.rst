.. highlight:: cpp

.. _lang-shiftout:

shiftOut()
==========

Shift out a byte of data, one bit at a time.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: shiftOut

Discussion
----------

This is a software implementation.  There is also a hardware :ref:`SPI
<spi>` library available which will be faster and consume less CPU
cycles than this function.

Note that the ``dataPin`` and ``clockPin`` must already be configured
to :ref:`OUTPUT <lang-constants-output>` mode by a call to
:ref:`pinMode() <lang-pinmode>`.

Also note that since shiftOut() outputs 1 byte (8 bits) at a time, it
requires multiple steps to output values larger than 255.

Examples
--------

To use these examples, replace ``dataPin`` and ``clockPin`` with the
numbers of the pins you want to use::

    /* MSBFIRST example */

    uint16 data = 500;
    // shift out high byte
    shiftOut(dataPin, clockPin, MSBFIRST, (data >> 8));
    // shift out low byte
    shiftOut(dataPin, clockPin, MSBFIRST, data);

    /* LSBFIRST serial */

    data = 500;
    // shift out low byte
    shiftOut(dataPin, clockPin, LSBFIRST, data);
    // shift out high byte
    shiftOut(dataPin, clockPin, LSBFIRST, (data >> 8));

Arduino Tutorial Example
------------------------

This Arduino example runs unmodified on the Maple.  For accompanying
circuit, see the `tutorial on controlling a 74HC595 shift register
<http://arduino.cc/en/Tutorial/ShiftOut>`_.

::

    //**************************************************************//
    //  Name    : shiftOutCode, Hello World                         //
    //  Author  : Carlyn Maw, Tom Igoe                              //
    //  Date    : 25 Oct, 2006                                      //
    //  Version : 1.0                                               //
    //  Notes   : Code for using a 74HC595 Shift Register           //
    //          : to count from 0 to 255                            //
    //**************************************************************//

    // Pin connected to ST_CP of 74HC595
    int latchPin = 8;
    // Pin connected to SH_CP of 74HC595
    int clockPin = 12;
    // Pin connected to DS of 74HC595
    int dataPin = 11;

    void setup() {
      // Set pins to output because they are addressed in the main loop
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }

    void loop() {
      // Count up routine
      for (int j = 0; j < 256; j++) {
        // Ground latchPin and hold low for as long as you are transmitting
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, j);
        // Return the latch pin high to signal chip that it
        // no longer needs to listen for information
        digitalWrite(latchPin, HIGH);
        delay(1000);
      }
    }

.. include:: /lang/cc-attribution.txt
