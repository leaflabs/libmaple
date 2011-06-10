.. highlight:: cpp

.. _lang-booleanvariables:

Booleans
========

A **boolean** holds one of two values, :ref:`true
<lang-constants-true>` or :ref:`false <lang-constants-false>`.  On a
Maple, each boolean variable has type ``bool``.

.. warning::

   On an Arduino, the type ``boolean`` is also provided.  While the
   Maple also has this type for compatibility, **its use is strongly
   discouraged**.  The ``bool`` type is a standard part of C++, while
   ``boolean`` is a non-standard extension that serves no purpose.

Example
-------

::

    // running is a boolean variable:
    bool running = false;

    void setup() {
        pinMode(BOARD_LED_PIN, OUTPUT);
        pinMode(BOARD_BUTTON_PIN, INPUT);
    }

    void loop() {
        if (isButtonPressed()) {
            // button is pressed
            running = !running;                     // toggle running variable
            digitalWrite(BOARD_LED_PIN, running)    // indicate via LED
        }
    }

See Also
--------

-  :ref:`Boolean constants <lang-constants-bool>`
-  :ref:`Boolean operators <lang-boolean>`
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt
