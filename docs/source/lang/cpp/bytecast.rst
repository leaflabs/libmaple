.. highlight:: cpp

.. _lang-bytecast:

byte() (cast)
=============

Converts a value to the :ref:`byte <lang-byte>` data type.

.. note::

   Casting to the byte type is provided for compatibility with
   Arduino.  However, the recommended Maple type for storing an 8-bit
   unsigned integer is ``uint8``. (C and C++ programmers: ``stdint.h``
   is also available).

   In order to cast a variable ``x`` to a ``uint8``, the
   following syntax can be used::

       uint8(x);

Syntax
------

``byte(x)``

Parameters
----------

**x**: a value of any integer type

Returns
-------

The value, converted to a ``byte``.  Note, however, that if the value
is larger than the maximum value you can store in a byte (255), then
the results might be strange and unexpected.

See Also
--------

-  :ref:`lang-byte`

.. include:: /arduino-cc-attribution.txt
