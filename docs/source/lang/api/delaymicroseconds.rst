.. highlight:: cpp

.. _lang-delaymicroseconds:

delayMicroseconds()
===================

Pauses the program for the amount of time (in microseconds)
specified as parameter. There are a thousand microseconds in a
millisecond, and a million microseconds in a second.

Library Documentation
---------------------

.. doxygenfunction:: delayMicroseconds


Example
-------

The following example configures pin number 8 to work as an output
pin, and sends a train of pulses with a period of roughly 100
microseconds::

    int outPin = 8;

    void setup() {
      pinMode(outPin, OUTPUT);      // sets the digital pin as output
    }

    void loop() {
      digitalWrite(outPin, HIGH);   // sets the pin on
      delayMicroseconds(50);        // pauses for 50 microseconds
      digitalWrite(outPin, LOW);    // sets the pin off
      delayMicroseconds(50);        // pauses for 50 microseconds
    }


Caveats and Known Issues
------------------------

The longest time ``delayMicroseconds()`` can delay is bounded by its
argument type and the STM32 clock rate to be (2^32 - 1) / 12
microseconds, or less than 6 minutes.  For longer pauses, use of
:ref:`lang-delay` is possible.

Arduino Compatibility
---------------------

While we have made every effort we could to ensure that the timing of
``delayMicroseconds()`` is as accurate as possible, we cannot
guarantee it will behave as the Arduino implementation down to the
microsecond, especially for smaller values of ``us``.

See Also
--------

-  :ref:`millis <lang-millis>`
-  :ref:`micros <lang-micros>`
-  :ref:`delay <lang-delay>`

.. include:: /arduino-cc-attribution.txt
