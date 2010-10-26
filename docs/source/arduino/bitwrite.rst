.. _arduino-bitwrite:

bitWrite(x, n, b)
=================

Description
-----------

(Macro) Writes a bit of a numeric variable.

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

Maple's version of ``bitWrite()`` is compatible with Arduino.

See also
--------

-  :ref:`bit() <arduino-bit>`
-  :ref:`bitRead() <arduino-bitRead>`
-  :ref:`bitSet() <arduino-bitSet>`
-  :ref:`bitClear() <arduino-bitClear>`
