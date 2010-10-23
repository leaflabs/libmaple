.. highlight:: cpp

.. _arduino-attachinterrupt:

attachInterrupt(interrupt, function, mode)
==========================================

.. doxygenfunction:: attachInterrupt

.. doxygenenum:: ExtIntTriggerMode

.. doxygentypedef:: voidFuncPtr

Discussion
----------

Specifies a function to call when an external interrupt occurs.
Replaces any previous function that was attached to the interrupt.
For more information on external interrupts on the Maple

Note
----

Inside the attached function, delay() won't work, and the value
returned by millis() will not increment. Serial data received while in
the function may be lost. You should declare as volatile any variables
that you modify within the attached function.


Using Interrupts
----------------

Interrupts are useful for making things happen automatically in
microcontroller programs, and can help solve timing problems. A
good task for using an interrupt might be reading a rotary encoder,
monitoring user input.



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
    volatile int state = LOW;
    
    void setup()
    {
      pinMode(maple_led_pin, OUTPUT);
      attachInterrupt(0, blink, CHANGE);
    }
    
    void loop()
    {
      digitalWrite(maple_led_pin, state);
    }
    
    void blink()
    {
      state = !state;
    }


Arduino Compatibility Note
--------------------------

Most Arduino boards have two external interrupts: numbers 0 (on
digital pin 2) and 1 (on digital pin 3). The Arduino Mega has an
additional four: numbers 2 (pin 21), 3 (pin 20), 4 (pin 19), and 5
(pin 18).


See also
--------


-  `detachInterrupt <http://arduino.cc/en/Reference/DetachInterrupt>`_


