.. highlight:: cpp

.. _arduino-doublecast:

double() (cast)
===============

Description
-----------

Converts a value to the :ref:`double <arduino-double>` floating point
data type.  Here is an example::

   int x = 2;
   double d = double(x);  // d now holds 2.0, a double value

The value ``x`` can be of any type.  However, if ``x`` is not a number
(like an ``int`` or ``long``), you will get strange results.

See the :ref:`double <arduino-double>` reference for details about the
precision and limitations of ``double`` values on the Maple.

See Also
--------

-  :ref:`double <arduino-double>`
-  :ref:`float <arduino-float>`
-  :ref:`float() <arduino-floatcast>`

.. include:: cc-attribution.txt
