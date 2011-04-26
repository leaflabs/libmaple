.. highlight:: cpp

.. _lang-longcast:

``long()`` (cast)
=================

Converts a value to the :ref:`long <lang-long>` data type.  Here is
an example::

    double d = 2.5;
    long i = long(d); // i holds "2L", an long value

The value inside of the parentheses (``long(...)``) can be of any type.
However, if it is not a numeric type (like ``double``, ``char``,
etc.), you will get strange results.

See the :ref:`long <lang-long>` reference for details about the
precision and limitations of ``long`` variables on the Maple.

See Also
--------

- :ref:`long <lang-long>`
- :ref:`long long <lang-longlong>`

.. include:: /arduino-cc-attribution.txt
