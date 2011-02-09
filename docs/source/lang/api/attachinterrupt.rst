.. highlight:: cpp

.. _lang-attachinterrupt:

attachInterrupt()
=================

Used to specify a function to call when an external interrupt (like an
GPIO changing from LOW to HIGH, a button getting pressed, etc.)
occurs.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. FIXME once breathe knows how to get the correct attachInterupt
.. (right now it's copying from HardwareTimer), replace with a
.. doxygenfunction directive

.. cpp:function:: void attachInterrupt(uint8 pin, voidFuncPtr handler, ExtIntTriggerMode mode)

   Registers an interrupt handler on a pin.

   The interrupt will be triggered on a given transition on the pin,
   as specified by the mode parameter.  The handler runs in interrupt
   context.  The new handler will replace whatever handler is
   currently registered for the pin, if any.

   *Parameters*

      - ``pin`` - Maple pin number

      - ``handler`` - Function to run upon external interrupt trigger.
        The handler should take no arguments, and have void return type.

      - ``mode`` - Type of transition to trigger on, e.g. falling,
        rising, etc.

.. doxygenenum:: ExtIntTriggerMode

.. doxygentypedef:: voidFuncPtr

Discussion
----------

Because the function will run in interrupt context, inside of it,
:ref:`lang-delay` won't work, and the value returned by
:ref:`lang-millis` will not increment. Serial data received while
in the function may be lost. You should declare as ``volatile`` any
global variables that you modify within the attached function.

There are a few constraints you should be aware of if you're using
more than one interrupt at a time; the :ref:`external-interrupts` page
has the details.

Using Interrupts
----------------

Interrupts are useful for making things happen automatically in
microcontroller programs, and can help solve timing problems. A
good task for using an interrupt might be reading a rotary encoder,
or monitoring user input.

If you wanted to insure that a program always caught the pulses
from a rotary encoder, never missing a pulse, it would make it very
tricky to write a program to do anything else, because the program
would need to constantly poll the sensor lines for the encoder, in
order to catch pulses when they occurred. Other sensors have a
similar interface dynamic too, such as trying to read a sound
sensor that is trying to catch a click, or an infrared slot sensor
(photo-interrupter) trying to catch a coin drop. In all of these
situations, using an interrupt can free the microcontroller to get
some other work done while not missing the doorbell.

Example
-------

::

    int maple_led_pin = 13;
    volatile int state = LOW; // must declare volatile, since it's
                              // modified within the blink handler

    void setup() {
      pinMode(maple_led_pin, OUTPUT);
      attachInterrupt(0, blink, CHANGE);
    }

    void loop() {
      digitalWrite(maple_led_pin, state);
    }

    void blink() {
      state = !state;
    }

Arduino Compatibility
---------------------

Most Arduino boards have two external interrupts: numbers 0 (on
digital pin 2) and 1 (on digital pin 3). The Arduino Mega has an
additional four: numbers 2 (pin 21), 3 (pin 20), 4 (pin 19), and 5
(pin 18).  On the Maple, you don't have to remember which interrupt
number goes with which pin -- just tell ``attachInterrupt()`` the pin
you want.

See also
--------

-  :ref:`detachInterrupt <lang-detachinterrupt>`
-  :ref:`external-interrupts`

.. include:: cc-attribution.txt
