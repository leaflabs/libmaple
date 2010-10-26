.. highlight:: cpp

.. _arduino-floatcast:

float() (cast)
==============

Description
-----------

Converts a value to the :ref:`float <arduino-float>` data type.  Here
is an example::

   int x = 2;
   float f = float(x);  // f now holds "2.0", a floating point value

The value ``x`` can be of any type.  However, if ``x`` is not a number
(like an ``int`` or ``long``), you will get strange results.

See the :ref:`float <arduino-float>` reference for details about the
precision and limitations of ``float`` values on the Maple.

See Also
--------

-  :ref:`float <arduino-float>`
