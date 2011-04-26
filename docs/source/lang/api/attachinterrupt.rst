.. highlight:: cpp

.. _lang-attachinterrupt:

attachInterrupt()
=================

Used to specify a function to call when an :ref:`external interrupt
<external-interrupts>` occurs.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. FIXME [doxygenfunction] once Breathe knows how to get the correct
.. attachInterupt (right now it's copying from HardwareTimer), replace
.. with a doxygenfunction directive

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
:ref:`lang-millis` will not increment. Serial data received while in
the function may be lost. You should declare as ``volatile`` any
global variables that you modify within the attached function.

There are a few limits you should be aware of if you're using more
than one interrupt at a time; the :ref:`External Interrupts
<external-interrupts-exti-line>` page has more information.

Example
-------

 ::

    volatile int state = LOW; // must declare volatile, since it's
                              // modified within the blink() handler

    void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);
      attachInterrupt(0, blink, CHANGE);
    }

    void loop() {
      digitalWrite(BOARD_LED_PIN, state);
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

See Also
--------

- :ref:`lang-detachinterrupt`
- :ref:`external-interrupts`

.. include:: /arduino-cc-attribution.txt
