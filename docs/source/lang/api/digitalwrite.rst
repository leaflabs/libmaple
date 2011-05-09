.. highlight:: cpp

.. _lang-digitalwrite:

digitalWrite()
==============

Write a :ref:`HIGH <lang-constants-high>` or a :ref:`LOW
<lang-constants-low>` value to a pin configured as :ref:`OUTPUT
<lang-constants-output>`.

Library Documentation
---------------------

.. doxygenfunction:: digitalWrite

Discussion
----------

If the pin has been configured as an ``OUTPUT`` with :ref:`pinMode()
<lang-pinmode>` its voltage will be set to the corresponding value:
3.3V for ``HIGH``, and 0V (ground) for ``LOW``.

Because it is soldered to an LED and resistor in series, your board's
:ref:`BOARD_LED_PIN <lang-board-values-led>` will respond slightly
more slowly as an output than the other pins.

Example
-------

The following example sets pin 13 to ``HIGH``, makes a one-second-long
delay, sets the pin back to ``LOW``, and delays again, causing a
blinking pattern (you could also use :ref:`lang-toggleled`)::

    void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);      // sets the digital pin as output
    }

    void loop() {
      digitalWrite(BOARD_LED_PIN, HIGH);   // sets the LED on
      delay(1000);                         // waits for a second
      digitalWrite(BOARD_LED_PIN, LOW);    // sets the LED off
      delay(1000);                         // waits for a second
    }

See Also
--------

- :ref:`pinMode <lang-pinmode>`
- :ref:`digitalRead <lang-digitalread>`
- :ref:`BOARD_LED_PIN <lang-board-values-led>`
- :ref:`lang-toggleled`
- :ref:`lang-togglepin`

.. include:: /arduino-cc-attribution.txt
