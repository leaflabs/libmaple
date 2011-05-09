.. highlight:: cpp

.. _lang-micros:

micros()
========

Returns the number of microseconds since the Maple board began running
the current program. This number will overflow (go back to zero),
after approximately 70 minutes.

.. note:: There are 1,000 microseconds in a millisecond, and 1,000,000
   microseconds in a second.

Library Documentation
---------------------

.. doxygenfunction:: micros

Example
-------

::

    unsigned int time;

    void setup() {
    }

    void loop() {
      SerialUSB.print("Time: ");
      time = micros();
      // prints time since program started
      SerialUSB.println(time);
      // wait a second so as not to send massive amounts of data
      delay(1000);
    }

See Also
--------

-  :ref:`millis() <lang-millis>`
-  :ref:`delay() <lang-delay>`
-  :ref:`delayMicroseconds() <lang-delaymicroseconds>`

.. include:: /arduino-cc-attribution.txt
