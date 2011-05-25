.. highlight:: cpp

.. _lang-toggleled:

toggleLED()
===========

*Toggle* the built-in LED: switch it from off to on, or on to off.

Library Documentation
---------------------

.. doxygenfunction:: toggleLED

Example
-------

.. _lang-toggleled-example:

This example sets up the board's LED pin for output, then toggles the
LED every 100 milliseconds::

    void setup() {
        pinMode(BOARD_LED_PIN, OUTPUT);
    }

    void loop() {
        toggleLED();
        delay(100);
    }


See Also
--------

- :ref:`BOARD_LED_PIN <lang-board-values-led>`
- :ref:`togglePin() <lang-togglepin>`
