.. _lang-bitread:

bitRead()
=========

(Macro) Gets the value of a bit in a number.

Syntax
------

``bitRead(x, n)``

Parameters
----------

* **x** the number from which to read the bit.

* **n** which bit to read, starting at 0 for the least-significant
  (rightmost) bit

Value
-----

The value of the bit (0 or 1).

Arduino Compatibility
---------------------

The Maple implementation of ``bitRead`` is compatible with Arduino.

See Also
--------

-  :ref:`lang-bit`
-  :ref:`lang-bitwrite`
-  :ref:`lang-bitset`
-  :ref:`lang-bitclear`

.. include:: /arduino-cc-attribution.txt
