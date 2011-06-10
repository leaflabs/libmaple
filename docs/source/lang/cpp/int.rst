.. highlight:: cpp

.. _lang-int:

``int``
=======

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
:ref:`unexpected complication <lang-bitshift-signbit-gotcha>` in
dealing with the :ref:`bitshift right operator (>>)
<lang-bitshift>`, however.

.. _lang-long:

The ``long`` type is a synonym for ``int``.

Here is an example of declaring an ``int`` variable named ``pin``,
then giving it value 13::

    int pin = 13;

The general syntax for declaring an ``int`` variable named ``var``,
then giving it value ``val``, looks like::

    int var = val;

.. _lang-int-overflow:

Integer Overflow
----------------

When ``int`` variables leave the range specified above, they
:ref:`roll over <lang-variables-rollover>` in the other direction.
Here are some examples::

       int x;
       x = -2,147,483,648;
       x--; // x now contains 2,147,483,647; rolled over "left to right"

       x = 2,147,483,647;
       x++; // x now contains -2,147,483,648; rolled over "right to left"

See Also
--------

-  :ref:`unsigned int <lang-unsignedint>`
-  :ref:`char <lang-char>`
-  :ref:`unsigned char <lang-unsignedchar>`
-  :ref:`long long <lang-longlong>`
-  :ref:`unsigned long long <lang-unsignedlonglong>`
-  :ref:`Integer Constants <lang-constants-integers>`
-  :ref:`Variables <lang-variables>`

.. include:: cc-attribution.txt
