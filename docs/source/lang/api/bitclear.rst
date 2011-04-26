.. _lang-bitclear:

bitClear()
==========

(Macro) Clears (writes a 0 to) a bit of a numeric variable.

Syntax
------

``bitClear(x, n)``

Parameters
----------

* **x** the numeric variable whose bit to clear

* **n** which bit to clear, starting at 0 for the least-significant
  (rightmost) bit

Returns
-------

Nothing.

Arduino Compatibility
---------------------

The Maple implementation of ``bitClear()`` is compatible with Arduino.

See Also
--------

-  :ref:`bit <lang-bit>`\ ()
-  :ref:`bitRead <lang-bitread>`\ ()
-  :ref:`bitWrite <lang-bitwrite>`\ ()
-  :ref:`bitSet <lang-bitset>`\ ()

.. include:: /arduino-cc-attribution.txt
