.. highlight:: cpp

.. _lang-floatcast:

``float()`` (cast)
==================

Converts a value to the :ref:`float <lang-float>` data type.  Here is
an example (see the :ref:`constants reference <lang-constants-fp>` for
an explanation of the "2.0f")::

   int x = 2;
   float f = float(x);  // f now holds 2.0f, a float value

The value ``x`` can be of any type.  However, if ``x`` is not a number
(like an ``int``), you will get strange results.

See the :ref:`float <lang-float>` reference for details about the
precision and limitations of ``float`` values on the Maple.

See Also
--------

-  :ref:`float <lang-float>`
-  :ref:`double <lang-double>`
-  :ref:`double() <lang-doublecast>`

.. include:: /arduino-cc-attribution.txt
