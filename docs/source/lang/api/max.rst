.. highlight:: cpp

.. _lang-max:

max()
=====

(Macro) Calculates the maximum of two numbers.

Syntax
------

::

    max(x, y)

Parameters
----------

**x**: the first number; may be any number or numeric expression.

**y**: the second number; may be any number or numeric expression.


Returns
-------

The larger of the two parameter values.

Example
-------

::

    sensVal = max(senVal, 20); // assigns sensVal to the larger of sensVal or 20
                               // (effectively ensuring that it is at least 20)

.. note:: Perhaps counter-intuitively, max() is often used to
   constrain the lower end of a variable's range, while :ref:`min()
   <lang-min>` is used to constrain the upper end of the range.

Warning
-------

Because of the way ``max()`` is implemented, avoid using other
functions inside the parentheses.  It may lead to incorrect results::

    max(a--, 0);   // avoid this - yields incorrect results

    a--;           // use this instead -
    max(a, 0);     // keep other operations outside max()

Arduino Compatibility
---------------------

The Maple implementation of ``max()`` is compatible with Arduino.

See Also
--------

-  :ref:`min() <lang-min>`
-  :ref:`constrain() <lang-constrain>`

.. include:: /arduino-cc-attribution.txt
