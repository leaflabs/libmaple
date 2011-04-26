.. highlight:: cpp

.. _lang-doublecast:

``double()`` (cast)
===================

Converts a value to the :ref:`double <lang-double>` floating point
data type.  Here is an example::

   int x = 2;
   double d = double(x);  // d now holds 2.0, a double value

The value ``x`` can be of any type.  However, if ``x`` is not a number
(like an ``int`` or ``long long``), you will get strange results.

See the :ref:`double <lang-double>` reference for details about the
precision and limitations of ``double`` values on the Maple.

See Also
--------

-  :ref:`double <lang-double>`
-  :ref:`float <lang-float>`
-  :ref:`float() <lang-floatcast>`

.. include:: /arduino-cc-attribution.txt
