.. highlight:: cpp

.. _lang-digitalread:

digitalRead()
=============

Reads the value from a specified digital pin, either :ref:`HIGH
<lang-constants-high>` or :ref:`LOW <lang-constants-low>`.


Library Documentation
---------------------

.. doxygenfunction:: digitalRead


Example
-------

The following example turns the LED on when the button is pressed::

    int ledPin = 13;     // LED connected to Maple pin 13
    int buttonPin = 38;  // BUT connected to Maple pin 38

    void setup() {
      pinMode(ledPin, OUTPUT);
      pinMode(buttonPin, INPUT);
    }

    void loop() {
      int val = digitalRead(buttonPin);   // reads the input pin
      digitalWrite(ledPin, val);
    }

Note
----

If the pin isn't connected to anything, ``digitalRead()`` can return
either HIGH or LOW (and this can change in a way that seems random).

Arduino Compatibility
---------------------

The Maple version of ``digitalRead()`` is compatible with Arduino.


See Also
--------

-  :ref:`pinMode <lang-pinMode>`
-  :ref:`digitalWrite <lang-digitalWrite>`





.. include:: cc-attribution.txt
