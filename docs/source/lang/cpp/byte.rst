.. highlight:: cpp

.. _lang-byte:

byte
====

The ``byte`` type stores a 1-byte (8-bit) unsigned integer number,
from 0 to 255.

.. warning::

   The ``byte`` type is provided for compatibility with Arduino.
   However, it is a non-standard extension.  The standard C++ type for
   storing an 8-bit unsigned integer is ``unsigned char``; we
   recommend using that instead.  (Your code will still work on an
   Arduino).


Example
-------

::

        byte b = 134;

See Also
--------

-  :ref:`byte() <lang-bytecast>` (casting a value to a byte)
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt
