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

.. TODO make the following paragraphs true, but refer the reader to
.. INPUT_PULLUP and INPUT_PULLDOWN:

If the pin is configured as an ``INPUT``, writing a ``HIGH`` value
with ``digitalWrite()`` will enable an internal pullup resistor.
Writing ``LOW`` will disable the pullup. The pullup resistor is enough
to light an LED dimly, so if LEDs appear to work, but very dimly, this
is a likely cause. The remedy is to set the pin to an output with the
:ref:`pinMode() <lang-pinmode>` function.

.. note:: Pin 13 is harder to use as an input than the other pins
   because it has an LED and resistor soldered to it in series. If you
   enable its internal pull-up resistor, it will likely hang at around
   1.1V instead of the expected 3.3V because the onboard LED and
   series resistor pull the voltage level down. If you must use pin 13
   as a digital input, use an external pull-down resistor.

Example
-------

The following example sets pin 13 to ``HIGH``, makes a one-second-long
delay, sets the pin back to ``LOW``, and delays again, causing a
blinking pattern::


    int ledPin = 13;                 // LED connected to digital pin 13

    void setup() {
      pinMode(ledPin, OUTPUT);      // sets the digital pin as output
    }

    void loop() {
      digitalWrite(ledPin, HIGH);   // sets the LED on
      delay(1000);                  // waits for a second
      digitalWrite(ledPin, LOW);    // sets the LED off
      delay(1000);                  // waits for a second
    }

See Also
--------

- :ref:`pinMode <lang-pinmode>`
- :ref:`digitalRead <lang-digitalread>`

.. include:: cc-attribution.txt
