.. _arduino-double:

double
======

Description
-----------

Double precision floating point number. Occupies 8 bytes.

Floating point numbers are not exact, and may yield strange results
when compared. For example ``6.0 / 3.0`` may not equal ``2.0``. You
should instead check that the absolute value of the difference between
the numbers is less than some small number.

Floating point math is also much slower than integer math in
performing calculations, so should be avoided if, for example, a loop
has to run at top speed for a critical timing function.  Programmers
often go to some lengths to convert floating point calculations to
integer math to increase speed.

For more information about floating point math, see the `Wikipedia
article <http://en.wikipedia.org/wiki/Floating_point>`_\ .

Floating-point numbers represent numbers with "decimal point", unlike
integral types, which always represent whole numbers. Floating-point
numbers are often used to approximate analog and continuous values
because they have greater resolution than integers.

The double implementation on the Maple uses twice the number of bytes
as a :ref:`float <arduino-float>`, with the corresponding gains in
precision.

Tip
---

Users who borrow code from other sources that includes double
variables may wish to examine the code to see if the implied
precision is different from that actually achieved on the Maple.


See Also
--------

-  :ref:`float <arduino-float>`

