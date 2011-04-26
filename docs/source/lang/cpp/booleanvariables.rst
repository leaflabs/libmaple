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

    int ledPin = 13;      // LED on pin 13
    int switchPin = 12;   // momentary switch on 12, other side connected to ground

    // running is a boolean variable:
    bool running = false;

    void setup() {
      pinMode(ledPin, OUTPUT);
      pinMode(switchPin, INPUT);
      digitalWrite(switchPin, HIGH);      // turn on pullup resistor
    }

    void loop() {
      if (digitalRead(switchPin) == LOW) {
        // switch is pressed - pullup keeps pin high normally
        delay(100);                        // delay to debounce switch
        running = !running;                // toggle running variable
        digitalWrite(ledPin, running)      // indicate via LED
      }
    }

See Also
--------

-  :ref:`Boolean constants <lang-constants-bool>`
-  :ref:`Boolean operators <lang-boolean>`
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt
