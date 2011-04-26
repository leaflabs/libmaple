.. highlight:: cpp

.. _lang-float:

``float``
=========

Single-precision floating point number. Occupies 4 bytes. On Maple,
the ``float`` type has a range of approximately -3.40282×10^38 to
3.40282×10^38; the ``float`` type is subject to the same
:ref:`overflow issues <lang-variables-rollover>` as any numeric data
type.

``float``\ s have only 6-7 decimal digits of precision. That means the
total number of digits, not the number to the right of the decimal
point.  You can get more precision by using a :ref:`double
<lang-double>` (which has a precision of about 16 decimal digits).

The following example declares a ``float`` value named ``myfloat``::

        float myfloat;

This example declares a ``float`` value named ``sensorCalibrate``,
with value 1.117::

        float sensorCalibrate = 1.117;

The general syntax for declaring a float named ``var`` with value
``val`` is::

        float var = val;

Here is a more extended example involving a :ref:`float cast
<lang-floatcast>`::

       int x;
       int y;
       float z;

       x = 1;
       y = x / 2;          // y now contains 0, ints can't hold fractions
       z = float(x) / 2; // z now contains .5

See Also
--------

-  :ref:`double <lang-double>`
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt
