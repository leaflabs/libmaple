.. highlight:: cpp

.. _lang-bitshift:

Bit Shift Operators (``<<``, ``>>``)
====================================

(Adapted from `The Bit Math Tutorial
<http://www.arduino.cc/playground/Code/BitMath>`_ in `The Arduino
Playground <http://www.arduino.cc/playground/Main/HomePage>`_\ )

There are two bit shift operators in C++: the left shift operator
``<<`` and the right shift operator ``>>``. These operators cause the
bits in the left operand to be shifted left or right by the number of
positions specified by the right operand.

More information on bitwise math can be obtained in the Wikipedia
article on `bitwise operations
<http://en.wikipedia.org/wiki/Bitwise_operation>`_\ , especially the
section on shifts in `C, C++, and Java
<http://en.wikipedia.org/wiki/Bitwise_operation#Shifts_in_C.2C_C.2B.2B.2C_C.23_and_Java>`_\ .


Syntax
------

``some_int << number_of_bits``

``some_int >> number_of_bits``


Parameters
----------

* **some_int** An integer value or variable.

* **number_of_bits** integer whose value is at most ``8 *
  sizeof(variable)`` (so ``number_of_bits`` can be at most 32 for
  ``int`` values, at most ``8`` for ``char`` values, etc.; the various
  integer sizes are summarized :ref:`in this table
  <lang-arithmetic-int-sizes>`\ ).



Example:
--------

Here are some examples of bit shifting, with the binary representation of the number in comments::

    int a = 5;        // binary: 101
    int b = a << 3;   // binary: 101000, or 40 in decimal
    int c = b >> 3;   // binary: 101, or back to 5 like we started with


When you left shift a value x by y bits (x << y), the leftmost y bits
in x are lost, literally shifted out of existence.  We'll do this
example with ``char`` values (which are integers in the range 0-255,
and take up 8 bits of memory)::

        char a = 5;        // binary (all 8 bits): 00000101
        char b = a << 7;   // binary:              10000000 - the first 1 in 101 was discarded


If you are certain that none of the ones in a value are being shifted
into oblivion, a simple way to think of the left-shift operator is
that it multiplies the left operand by 2 raised to the right operand
power (in math notation, ``x << y`` equals x * 2\ :sup:`y`\ , as long
as none of the bits of x get shifted out). For example, to generate
powers of 2, the following expressions can be employed::

        1 <<  0  ==    1
        1 <<  1  ==    2
        1 <<  2  ==    4
        1 <<  3  ==    8
        ...
        1 <<  8  ==  256
        1 <<  9  ==  512
        1 << 10  == 1024
        ...

.. _lang-bitshift-signbit-gotcha:

When you shift x right by y bits (``x >> y``), and the highest bit in
x is a 1, the behavior depends on the exact data type of x. If x is of
type ``int``, the highest bit is special, and determines whether x is
negative or not; the details are too complicated to explain here, but
they are thoroughly explained in the Wikipedia article on `two's
complement arithmetic
<http://en.wikipedia.org/wiki/Two%27s_complement>`_\ , which the
system most computers use to store integers. In that case, the sign
bit is copied into lower bits, for esoteric historical reasons::

    int x = -16;     // binary (all 32 bits): 11111111111111111111111111110000
    int y = x >> 3;  // binary:               11111111111111111111111111111110



This behavior, called "sign extension", is often not what you
want. You probably wish zeros to be shifted in from the left.  It
turns out that the right shift rules are different for ``unsigned
int`` values, so you can use a type cast to suppress ones being copied
from the left::

    int x = -16;                  // binary: 11111111111111111111111111110000
    int y = (unsigned int)x >> 3; // binary: 00011111111111111111111111111110



If you are careful to avoid sign extension, you can use the
right-shift operator, ``>>``, as a way to divide by powers of 2. For
example::

   int x = 1000;
   int y = x >> 3;   // integer division of 1000 by 8, causing y = 125.


Arduino Compatibility
---------------------

Since it's part of the C++ language, bit shifting on the Maple is
compatible with the Arduino; however, you should keep in mind that the
Maple has bigger integer types (as in, more bits) than the Arduino.

Since the STM32 is a 32-bit processor, the ``int`` type takes up 32
bits instead of 16, like on Arduino's 16-bit microcontroller.  This
means that you can shift left, like ``x << y``, with bigger values of
``y`` on the Maple before ones in ``x`` start to get shifted out.

To calculate the number of bits of an integer type on the Maple,
multiply its size in bytes (see :ref:`this table
<lang-arithmetic-int-sizes>` for these) by 8, since there are 8
bits in 1 byte.  For example, a ``short`` takes up 2 bytes of memory,
or 2 * 8 = 16 bits.

See Also
--------

-  :ref:`lang-bit`
-  :ref:`lang-bitread`
-  :ref:`lang-bitwrite`
-  :ref:`lang-bitclear`

.. include:: /arduino-cc-attribution.txt
