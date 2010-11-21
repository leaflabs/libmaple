.. highlight:: cpp

.. _arduino-floatcast:

float() (cast)
==============

Description
-----------

Converts a value to the :ref:`float <arduino-float>` data type.  Here
is an example (see the :ref:`constants reference
<arduino-constants-fp-f>` for an explanation of the "2.0f")::

   int x = 2;
   float f = float(x);  // f now holds 2.0f, a float value

The value ``x`` can be of any type.  However, if ``x`` is not a number
(like an ``int``), you will get strange results.

See the :ref:`float <arduino-float>` reference for details about the
precision and limitations of ``float`` values on the Maple.

See Also
--------

-  :ref:`float <arduino-float>`
-  :ref:`double <arduino-double>`
-  :ref:`double() <arduino-doublecast>`

.. include:: cc-attribution.txt
