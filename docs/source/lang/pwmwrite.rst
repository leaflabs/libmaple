.. highlight:: cpp

.. _lang-pwmwrite:

pwmWrite()
==========

Writes a :ref:`PWM wave <pwm>` to a pin.  You can use this to make an
LED get brighter or dimmer, control a servomotor, etc. After a call to
pwmWrite(), the pin will output a steady square wave with the given
duty cycle.  You can change the duty cycle later by calling pwmWrite()
again with the same pin and a different duty.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: pwmWrite

Example
-------

Sets the output to the LED proportional to the value read from the
potentiometer (adapted for Maple from the Arduino `analogWrite()
reference <http://www.arduino.cc/en/Reference/AnalogWrite>`_)::


    int ledPin = 13;      // LED connected to pin 13 (Maple)
    int analogPin = 3;    // potentiometer connected to analog pin 3
    int val = 0;          // variable to store the read value

    void setup() {
      pinMode(ledPin, OUTPUT);   // sets the LED pin as output

      pinMode(analogPin, PWM);   // sets the potentiometer pin as PWM
                                 // output
    }

    void loop() {
      val = analogRead(analogPin);   // read the input pin

      analogWrite(ledPin, val / 16);  // analogRead values go from 0 to 4095,
                                      // analogWrite values from 0 to 65535
    }

See Also
--------

-  :ref:`Maple PWM tutorial <pwm>`
