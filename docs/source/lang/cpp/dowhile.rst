.. highlight:: cpp

.. _lang-dowhile:

``do``/``while``
================

A ``do`` loop works in the same manner as a :ref:`while
<lang-while>` loop, with the exception that the condition is tested
at the end of the loop, so the ``do`` loop will *always* run at least
once.

This is the basic syntax::

    do {
        // statement block
    } while (test condition);

Example::

    do {
      delay(50);          // wait for sensors to stabilize
      x = readSensors();  // check the sensors
    } while (x < 100);

.. include:: /arduino-cc-attribution.txt
