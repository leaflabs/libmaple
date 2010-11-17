.. _arduino-bitread:

bitRead()
=========

Description
-----------

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


See also
--------


-  :ref:`arduino-bit`
-  :ref:`arduino-bitwrite`
-  :ref:`arduino-bitset`
-  :ref:`arduino-bitclear`


.. include:: cc-attribution.txt