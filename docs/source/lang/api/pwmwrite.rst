.. highlight:: cpp

.. _lang-pwmwrite:

pwmWrite()
==========

Writes a :ref:`PWM wave <pwm>` to a pin.  You can use this to make an
LED get brighter or dimmer, control a servomotor, etc. After a call to
pwmWrite(), the pin will output a steady square wave with the given
duty cycle.  You can change the duty cycle later by calling pwmWrite()
again with the same pin and a different duty.

On the Maple, the pins which support PWM are: 0, 1, 2, 3, 5, 6, 7, 8,
9, 11, 12, 14, 24, 27, and 28.

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
    int val = 0;          // variable to store the read value

    void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);   // sets the LED pin as output

      pinMode(analogPin, PWM);   // sets the potentiometer pin as PWM
                                 // output
    }

    void loop() {
      val = analogRead(analogPin);   // read the input pin

      analogWrite(BOARD_LED_PIN, val / 16);  // analogRead values go from 0
                                             // to 4095, analogWrite values
                                             // from 0 to 65535
    }

See Also
--------

-  :ref:`Maple PWM tutorial <pwm>`
