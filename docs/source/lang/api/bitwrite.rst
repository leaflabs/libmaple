.. highlight:: cpp

.. _lang-bitwrite:

bitWrite()
==========

(Macro) Writes a bit of a numeric variable.

Syntax
------

::

   bitWrite(x, n, b)

Parameters
----------

**x**: the numeric variable whose bit to write.

**n**: which bit of the number to write, starting at 0 for the
least-significant (rightmost) bit.

**b**: the value to write to the bit (0 or 1).

Returns
-------

Nothing.

Arduino Compatibility
---------------------

Maple's implementation of ``bitWrite()`` is compatible with Arduino.

See Also
--------

-  :ref:`bit() <lang-bit>`
-  :ref:`bitRead() <lang-bitRead>`
-  :ref:`bitSet() <lang-bitSet>`
-  :ref:`bitClear() <lang-bitClear>`

.. include:: /arduino-cc-attribution.txt
