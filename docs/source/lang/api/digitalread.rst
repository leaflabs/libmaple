.. highlight:: cpp

.. _lang-digitalread:

digitalRead()
=============

Reads the value from a specified digital pin, either :ref:`HIGH
<lang-constants-high>` or :ref:`LOW <lang-constants-low>`.

Library Documentation
---------------------

.. doxygenfunction:: digitalRead

Discussion
----------

If the pin isn't connected to anything, ``digitalRead()`` can return
either HIGH or LOW (and this will change in a way that seems random).

Example
-------

The following example turns the LED on or off when the button is pressed::

    void setup() {
      pinMode(BOARD_LED_PIN, OUTPUT);
      pinMode(BOARD_BUTTON_PIN, INPUT);
    }

    void loop() {
      int val = digitalRead(BOARD_BUTTON_PIN);   // reads the input pin
      togglePin(BOARD_LED_PIN, val);
    }

Arduino Compatibility
---------------------

The Maple version of ``digitalRead()`` is compatible with Arduino.

See Also
--------

- :ref:`BOARD_BUTTON_PIN <lang-board-values-but>`
- :ref:`lang-isButtonPressed`
- :ref:`lang-pinmode`
- :ref:`lang-digitalWrite`
- :ref:`lang-togglepin`

.. include:: /arduino-cc-attribution.txt
