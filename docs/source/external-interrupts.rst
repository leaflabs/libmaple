.. highlight:: cpp

.. _external-interrupts:

External Interrupts
===================

External interrupts can be used to trigger routines to run in response
to changes in voltage on a pin. Each GPIO pin on the Maple can be used
to detect transitions such as when the voltage goes from low to high,
or from high to low. This technique can be used to avoid unnecessary
polling of the state of a pin.

.. _contents: Contents
   :local:


Overview
--------

External interrupts are often used to detect when events happen
outside of the microcontroller. These can be used to tell the Maple
when events happen, such as when a sensor has data ready to be read,
or when a button has been pushed. When such an event happens, an
interrupt is raised and the Maple can react to it with a preset
*interrupt handler*.

Every GPIO pin on the Maple can be used as an external interrupt,
subject to certain constraints; there can be a maximum of 16 different
external interrupts set up at a time on the Maple. This is because the
external interrupt lines on the STM32 are multiplexed between GPIO
ports. In effect, this means that every pin on the Maple maps to a
certain EXTI line, and within that EXTI line, only one of the pins
that maps to it can be used as an external interrupt at a time.

The following table shows which pins can be used on which lines.

.. list-table::
   :widths: 1 1
   :header-rows: 1

   * - EXTI Line
     - Maple pins
   * - EXTI0
     - 2, 15, 27
   * - EXTI1
     - 3, 16, 28
   * - EXTI2
     - 1, 17, 25
   * - EXTI3
     - 0, 18
   * - EXTI4
     - 10, 19
   * - EXTI5
     - 4, 13, 20
   * - EXTI6
     - 5, 12, 35
   * - EXTI7
     - 9, 11, 36
   * - EXTI8
     - 6, 14, 37
   * - EXTI9
     - 7, 25, 28
   * - EXTI10
     - 8, 26, 29
   * - EXTI11
     - 30
   * - EXTI12
     - 31
   * - EXTI13
     - 21, 32
   * - EXTI14
     - 22, 33
   * - EXTI15
     - 23, 34

.. note::

   You should set the :ref:`pin mode <lang-pinmode>` of your
   desired pin to an input mode (e.g ``INPUT`` or ``INPUT_FLOATING``,
   ``INPUT_PULLUP``, ``INPUT_PULLDOWN``).


Function Reference
------------------

.. doxygenfunction:: attachInterrupt

.. doxygenfunction:: detachInterrupt

.. doxygenenum:: ExtIntTriggerMode

.. doxygentypedef:: voidFuncPtr


Code example
------------

Blink the LED on every transition::

    int pin = 13;
    volatile int state = LOW;

    void setup() {
      pinMode(pin, OUTPUT);
      pinMode(0, INPUT_FLOATING);
      attachInterrupt(0, blink, CHANGE);
    }

    void loop() {
      digitalWrite(pin, state);
    }

    void blink() {
      state = !state;
    }


Recommended Reading
-------------------

* STMicro documentation for STM32F103RB microcontroller:

      * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
      * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
