.. _lang-lowbyte:

lowByte()
=========

Extracts the low-order (rightmost) byte of a variable (e.g. a
word).

Syntax
------

lowByte(x)

Parameters
----------

**x**: a value of any type.  However, if a non-integral type is used,
the results will be strange.

Returns
-------

The low byte's value (this will be between 0 and 255).

.. include:: /arduino-cc-attribution.txt
