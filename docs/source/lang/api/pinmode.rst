.. highlight:: cpp

.. _lang-pinmode:

pinMode()
=========

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: pinMode

.. _lang-pinmode-wiringpinmode:

.. doxygenenum:: WiringPinMode

Discussion
----------

pinMode() is usually called within :ref:`lang-setup` in order to
configure a pin for a certain usage (although it may be called
anywhere).

Example
-------

This example uses pinMode() to set up the pin connected to the
built-in LED as an output.  Once this is done,
:ref:`lang-digitalwrite` can be used to turn the pin ``HIGH`` and
``LOW``, which turn the LED on and off.

::

    void setup() {
        pinMode(BOARD_LED_PIN, OUTPUT);      // sets the LED pin as output
    }

    void loop() {
        digitalWrite(BOARD_LED_PIN, HIGH);   // sets the LED on
        delay(1000);                         // waits for a second
        digitalWrite(BOARD_LED_PIN, LOW);    // sets the LED off
        delay(1000);                         // waits for a second
    }

Arduino Compatibility
---------------------

.. TODO check out Arduino vs. Maple static discilpline cutoffs to
.. ensure accuracy of following:

On Maple, pinMode() supports the ``INPUT`` and ``OUTPUT`` modes in the
same way as Arduino (however, remember that the Maple, as a 3.3V
device, will only drive 3.3V to an ``OUTPUT`` pin that has been set
``HIGH``, instead of 5V like on Arduino).

``INPUT_ANALOG`` and ``PWM`` modes were added because the Maple
doesn't separate the analog and digital pins the same way Arduino
does.  Unlike on Arduino, you **must call** pinMode() to set up a pin
for these purposes before a call to, e.g., :ref:`lang-analogRead`.
This should only add a few lines to your :ref:`lang-setup` function.

.. TODO [0.1.0] verify following before putting it in:

.. ``OUTPUT_OPEN_DRAIN``, ``INPUT_PULLUP``, ``INPUT_PULLDOWN``, and
.. ``PWM_OPEN_DRAIN`` modes represent functionality not currently
.. available on Arduino boards.

See Also
--------

- :ref:`lang-board-values`
- :ref:`lang-constants`
- :ref:`lang-digitalwrite`
- :ref:`lang-digitalread`
- :ref:`gpio`

.. include:: /arduino-cc-attribution.txt
