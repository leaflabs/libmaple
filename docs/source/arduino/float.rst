.. highlight:: cpp

.. _arduino-float:

float
=====

.. TODO move all the useful examples over to arduino/double.rst.  We
.. want to discourage using floats, since most of the common cmath
.. functions are only declared with doubles.

Description
-----------

Single-precision floating point number.  ``float`` values can be as
large as 3.4028235E+38 and as low as -3.4028235E+38. They are stored
as 32 bits (4 bytes) of information.

``float``\ s have only 6-7 decimal digits of precision. That means the total
number of digits, not the number to the right of the decimal point.
You can get more precision by using a :ref:`double <arduino-double>`
(which has a precision of about 16 decimal digits).

The following example declares a ``float`` value named ``myfloat``::

        float myfloat;

This example declares a ``float`` value named ``sensorCalibrate``,
with value 1.117::

        float sensorCalibrate = 1.117;

The general syntax for declaring a float named ``var`` with value
``val`` is::

        float var = val;

Here is a more extended example involving a :ref:`float cast
<arduino-floatcast>`::

       int x;
       int y;
       float z;
    
       x = 1;
       y = x / 2;          // y now contains 0, ints can't hold fractions
       z = float(x) / 2; // z now contains .5

See Also
--------

-  :ref:`int <arduino-int>`
-  :ref:`double <arduino-double>`
-  :ref:`Variables <arduino-variables>`



.. include:: cc-attribution.txt