.. highlight:: cpp

.. _lang-map:

map()
=====

Re-maps a number from one range to another.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: map

Discussion
----------

``map()`` does not constrain values to within the range, because
out-of-range values are sometimes intended and useful. The
:ref:`constrain() <lang-constrain>` macro may be used either before or
after this function, if limits to the ranges are desired.

Note that the "lower bounds" of either range may be larger or smaller
than the "upper bounds" so that ``map()`` may be used to reverse a
range of numbers; for example::

    y = map(x, 1, 50, 50, 1);

The function also handles negative numbers well, so that this
example ::

    y = map(x, 1, 50, 50, -100);

is also valid.

The ``map()`` function uses integer math (its arguments and return
values all have type :ref:`long <lang-long>`), so it will not generate
fractions, when the math might indicate that it should do so.
Fractional remainders are truncated, and are not rounded or averaged.

Example
-------

::

    /* Map an ADC reading (12 bits) to 16-bit PWM (0 to 65,535) */

    void setup() {
        pinMode(0, INPUT_ANALOG);
        pinMode(9, PWM);
    }

    void loop() {
        int val = analogRead(0);
        val = map(val, 0, 4095, 0, 65535);
        analogWrite(9, val);
    }


See Also
--------

-  :ref:`constrain() <lang-constrain>`

.. include:: /arduino-cc-attribution.txt
