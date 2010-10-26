.. highlight:: cpp

.. _arduino-charcast:

char() (cast)
=============

Description
-----------

Converts a value to the :ref:`char <arduino-char>` data type.

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

-  :ref:`char <arduino-char>`
