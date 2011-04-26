.. highlight:: cpp

.. _lang-charcast:

``char()`` (cast)
=================

Converts a value to the :ref:`char <lang-char>` data type.

Syntax
------

``char(x)``

Parameters
----------

**x**: a value of any type

Returns
-------

The value, converted to a ``char``.  Note, however, that if the value
is outside the range of a ``char`` (-128 to 127), then the results
might be strange and unexpected.

See Also
--------

-  :ref:`char <lang-char>`

.. include:: /arduino-cc-attribution.txt
