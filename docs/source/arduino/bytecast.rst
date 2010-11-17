.. highlight:: cpp

.. _arduino-bytecast:

byte() (cast)
=============

Description
-----------

Converts a value to the :ref:`byte <arduino-byte>` data type.

.. warning::

   Casting to the byte type is provided for compatibility with
   Arduino.  However, ``byte`` is a non-standard type.  The standard
   C++ type for storing an 8-bit unsigned integer is ``unsigned
   char``, and we recommend using that instead.

   In order to cast a variable ``x`` to an ``unsigned char``, the
   following syntax can be used::

       (unsigned char)(x);

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

-  :ref:`arduino-byte`




.. include:: cc-attribution.txt