.. highlight:: cpp

.. _lang-millis:

millis()
========

Returns the number of milliseconds since the Maple board began running
the current program. This number will overflow (go back to zero) after
approximately 50 days.

Library Documentation
---------------------

.. doxygenfunction:: millis

Example
-------

The following time prints the value returned by ``millis()`` roughly
once per second::

    unsigned int time;

    void setup() {
    }

    void loop() {
      SerialUSB.print("Time: ");
      time = millis();
      // prints time since program started
      Serial.println(time);

      // wait a second so as not to send massive amounts of data
      delay(1000);
    }

Tip
---

Since the return value for ``millis()`` is an :ref:`unsigned long
<lang-unsignedlong>`, overflow errors may occur if you try to do math
with other data types, such as :ref:`chars <lang-char>`.

See Also
--------

- :ref:`micros <lang-micros>`
- :ref:`delay <lang-delay>`
- :ref:`delayMicroseconds <lang-delaymicroseconds>`

.. include:: /arduino-cc-attribution.txt
