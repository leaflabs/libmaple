.. highlight:: cpp

.. _arduino-int:

int
===

Description
-----------

The ``int`` data type represents integers.  Integers are your primary
data type for number storage, and store a 4 byte value. This yields a
range of -2,147,483,648 to 2,147,483,647 (minimum value of -2^31 and a
maximum value of (2^31) - 1; that's about negative 2 billion to
positive 2 billion).

An ``int`` stores a negative number with a technique called `two's
complement math
<http://en.wikipedia.org/wiki/Two%27s_complement#Explanation>`_\ .
The highest bit in an ``int``, sometimes refered to as the "sign" bit,
flags the number as a negative number.  (See the linked article on
two's complement for more information).

The Maple takes care of dealing with negative numbers for you, so that
arithmetic operations work mostly as you'd expect. There can be an
:ref:`unexpected complication <arduino-bitshift-signbit-gotcha>` in
dealing with the :ref:`bitshift right operator (>>)
<arduino-bitshift>`, however.

Here is an example of declaring an ``int`` variable named ``ledPin``,
then giving it value 13::

    int ledPin = 13;

The general syntax for declaring an ``int`` variable named ``var``,
then giving it value ``val``, looks like::

    int var = val;

.. _arduino-int-overflow:

Integer Overflow
----------------

When ``int`` variables leave the range specified above, they "roll
over" in the other direction.  It's like in the game *Pac-Man* -- when
Pac-Man goes past the right edge of the screen, he reappears on the
left, and when he goes past the left side of the screen, he reappears
on the right.  Here are some examples::

       int x;
       x = -2,147,483,648;
       x--; // x now contains 2,147,483,647; rolled over "left to right"

       x = 2,147,483,647;
       x++; // x now contains -2,147,483,648; rolled over "right to left"

See Also
--------

-  :ref:`unsigned int <arduino-unsignedint>`
-  :ref:`char <arduino-char>`
-  :ref:`unsigned char <arduino-unsignedchar>`
-  :ref:`long <arduino-long>`
-  :ref:`unsigned long <arduino-unsignedlong>`
-  :ref:`Integer Constants <arduino-constants-integers>`
-  :ref:`Variables <arduino-variables>`


.. include:: cc-attribution.txt