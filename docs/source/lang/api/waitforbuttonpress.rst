.. highlight:: cpp

.. _lang-waitforbuttonpress:

waitForButtonPress()
====================

Wait for the board's built-in button to be pressed, possibly with
timeout.  The button is labeled "BUT" on the board's silkscreen.  Its
pin number is the constant :ref:`BOARD_BUTTON_PIN
<lang-board-values-but>`.

Library Documentation
---------------------

.. doxygenfunction:: waitForButtonPress


Example
-------

.. _lang-waitforbuttonpress-example:

This example sets up the board's button pin as an input, then prints a
message very time the button is pressed.

::

    void setup() {
        pinMode(BOARD_BUTTON_PIN, INPUT);
    }

    void loop() {
        waitForButtonPress();
        SerialUSB.println("You pressed the button!");
    }

See Also
--------

- :ref:`Board-specific values <lang-board-values>`
- :ref:`BOARD_BUTTON_PIN <lang-board-values-but>`
- :ref:`lang-isbuttonpressed`
