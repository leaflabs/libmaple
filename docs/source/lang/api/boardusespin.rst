.. highlight:: cpp

.. _lang-boardusespin:

boardUsesPin()
==============

Each LeafLabs board connects some pins to external hardware.  The most
important examples of this are the pins connected to the built-in LED
and button.  You can check if a board uses a particular pin using this
function.

Library Documentation
---------------------

.. doxygenfunction:: boardUsesPin

See Also
--------

- :ref:`Board-specific values <lang-board-values>`
- :ref:`boardUsedPins <lang-board-values-used-pins>`
- :ref:`BOARD_LED_PIN <lang-board-values-led>`
- :ref:`toggleLED() <lang-toggleled>`
- :ref:`BOARD_BUTTON_PIN <lang-board-values-but>`
- :ref:`isButtonPressed() <lang-isbuttonpressed>`
- :ref:`waitForButtonPress() <lang-waitforbuttonpress>`
