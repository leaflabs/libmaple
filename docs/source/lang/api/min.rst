.. highlight:: cpp

.. _lang-min:

min()
=====

(Macro) Calculates the minimum of two numbers.

Syntax
------

::

    min(x,y)

Parameters
----------

**x**: the first number; may be any number or numeric expression.

**y**: the second number; may be any number or numeric expression.

Returns
-------

The smaller of the two numbers.

Example
-------

::

    sensVal = min(sensVal, 100); // assigns sensVal to the smaller of sensVal or 100
                                 // ensuring that it never gets above 100.


.. note:: Perhaps counter-intuitively, max() is often used to
   constrain the lower end of a variable's range, while min() is used
   to constrain the upper end of the range.


Warning
-------

Because of the way ``min()`` is implemented, avoid using other
functions inside the parentheses. It may lead to incorrect results::

    min(a++, 100);   // avoid this - yields incorrect results

    a++;            // use this instead -
    min(a, 100);    // keep other operations outside min()

Arduino Compatibility
---------------------

The Maple version of ``min()`` is compatible with Arduino.

See Also
--------

-  :ref:`max() <lang-max>`
-  :ref:`constrain() <lang-constrain>`

.. include:: /arduino-cc-attribution.txt
