.. _lang-bit:

bit()
=====

(Macro) Computes the value of an (unsigned) integer with the specified
bit set (``bit(0)`` is 1, ``bit(1)`` is 2, ``bit(2)`` is 4, then 8,
16, 32, etc.).

Syntax
------

``bit(n)``

Parameters
----------

* **n** the bit to set.

Value
-----

The value of an integer with the given bit set.

Arduino Compatibility
---------------------

The Maple implementation of ``bit()`` is compatible with Arduino.

See Also
--------

-  :ref:`lang-bitread`
-  :ref:`lang-bitwrite`
-  :ref:`lang-bitset`
-  :ref:`lang-bitclear`

.. include:: /arduino-cc-attribution.txt
