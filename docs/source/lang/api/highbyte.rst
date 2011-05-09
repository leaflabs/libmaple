.. highlight:: cpp

.. _lang-highbyte:

highByte()
==========

(Macro) Extracts the second lowest byte of an integral data type.

.. warning:: This macro is provided for compatibility with Arduino
   only.  It returns the second-least significant byte in an integral
   value.  It makes sense to call this the "high" byte on a 16-bit
   ``int`` microcontroller like the Atmel chips on Arduinos, but it
   makes no sense at all on a 32-bit microcontroller like the STM32s
   in the Maple line.

   In short: we provide this so that existing Arduino code works as
   expected, but **strongly discourage its use** in new programs.

Syntax
------

::

  highByte(x)

Parameters
----------

**x**: a value of any integral type.

Returns
-------

Second lowest byte in **x**.

Example
-------

::

    int x = 0xDEADBEEF;
    SerialUSB.println(x, HEX); // prints "BE"

Arduino Compatibility
---------------------

The Maple version of ``highByte()`` is compatible with Arduino.

See Also
--------

-  :ref:`lowByte() <lang-lowbyte>`

.. include:: /arduino-cc-attribution.txt
