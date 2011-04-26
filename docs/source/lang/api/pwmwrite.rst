.. highlight:: cpp

.. _lang-pwmwrite:

pwmWrite()
==========

Writes a :ref:`PWM wave <pwm>` to a pin.  You can use this to make an
LED get brighter or dimmer, control a servomotor, etc. After a call to
pwmWrite(), the pin will output a steady square wave with the given
duty cycle.  You can change the duty cycle later by calling pwmWrite()
again with the same pin and a different duty.

The pins which support PWM have ``PWM`` listed underneath their number
on your board's silkscreen.  These pin numbers are available to your
program in the :ref:`boardPWMPins <lang-board-values-pwm-pins>`
board-specific array.  The number of pins which are capable of PWM on
your board is given by the ``BOARD_NR_PWM_PINS`` constant.  These
values are documented for each board in the :ref:`Board Hardware
Documentation <index-boards>` pages.

The Arduino function :ref:`analogWrite() <lang-analogwrite>` is an
alias for ``pwmWrite()``, but it is badly named, and its use is
discouraged.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: pwmWrite

Example
-------

Sets the output to the LED proportional to the value read from the
potentiometer::

    int analogPin = 3;    // potentiometer connected to analog pin 3

    void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);   // sets the LED pin as output

      pinMode(analogPin, INPUT_ANALOG); // sets the potentiometer pin as
                                        // analog input
    }

    void loop() {
      int val = analogRead(analogPin);        // read the input pin

      pwmWrite(BOARD_LED_PIN, val * 16);  // analogRead values go from 0
                                          // to 4095, pwmWrite values
                                          // from 0 to 65535, so scale roughly
    }

See Also
--------

- :ref:`Maple PWM tutorial <pwm>`
- :ref:`boardPWMPins <lang-board-values-pwm-pins>`
