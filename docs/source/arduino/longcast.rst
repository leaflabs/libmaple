.. highlight:: cpp

.. _arduino-longcast:

long()
======

Description
-----------

Converts a value to the :ref:`long <arduino-long>` data type.  Here is
an example::

    double d = 2.5;
    long i = long(d); // i holds "2L", an long value

The value inside of the parentheses (``long(...)``) can be of any type.
However, if it is not a numeric type (like ``double``, ``char``,
etc.), you will get strange results.

See the :ref:`long <arduino-long>` reference for details about the
precision and limitations of ``long`` variables on the Maple.

See Also
--------

-  :ref:`long <arduino-long>`


.. include:: cc-attribution.txt