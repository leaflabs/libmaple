.. highlight:: cpp

.. _lang-intcast:

``int()`` (cast)
================

Converts a value to the :ref:`int <lang-int>` data type.  Here is
an example::

    double d = 2.5;
    int i = int(d); // i holds "2", an int value

The value inside of the parentheses (``int(...)``) can be of any type.
However, if it is not a numeric type (like ``double``, ``char``,
etc.), you will get strange results.

See the :ref:`int <lang-int>` reference for details about the
precision and limitations of ``int`` variables on the Maple.

See Also
--------

-  :ref:`int <lang-int>`

.. include:: /arduino-cc-attribution.txt
