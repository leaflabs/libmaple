.. highlight:: cpp

.. _lang-arithmetic:

Arithmetic Operators (``+``, ``-``, ``*``, ``/``)
=================================================

The operators ``+``, ``-``, ``*``, and ``/`` respectively evaluate to
the sum, difference, product, or quotient (respectively) of the two
operands. The operation is conducted using the data type of the
operands, so, for example, ``9 / 4`` gives ``2`` since 9 and 4 are
:ref:`int variables <lang-int>`.

This also means that the operation can overflow if the result is
larger than that which can be stored in the data type (e.g. adding 1
to an :ref:`lang-int` with the value 2,147,483,647 gives
-2,147,483,648).

.. _lang-arithmetic-typeconversion:

If the operands are of different types, the "larger" type is used for
the calculation.  If one of the numbers (operands) are of the type
**float** or of type **double**, floating point math will be used for
the calculation.

.. note:: The specifics of these rules are beyond the scope of this
   documentation; for more information, see `The C++ Programming
   Language <http://www2.research.att.com/~bs/3rd.html>`_\ , by Bjarne
   Stroustroup, Appendix C, especially §§C.4-C.6, or `this WikiBooks
   entry on C++ type conversion
   <http://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Variables/Type_Casting#Automatic_type_conversion>`_.

.. note:: For more information on how computers represent integers,
   see the Wikipedia page on `two's complement
   <http://en.wikipedia.org/wiki/Two's_complement>`_.

.. contents:: Contents
   :local:

Examples
--------

 ::

    y = y + 3;
    x = x - 7;
    i = j * 6;
    r = r / 5;


Syntax
------

 ::

    result = value1 + value2;
    result = value1 - value2;
    result = value1 * value2;
    result = value1 / value2;


Parameters
----------

**value1**: any numeric variable or constant

**value2**: any numeric variable or constant

Programming Tips
----------------

- Know that :ref:`integer constants <lang-constants-integers>`
  default to :ref:`int <lang-int>`, so some constant calculations
  may overflow (e.g., 200000 * 5000000 will yield a negative result).

- Choose variable sizes that are large enough to hold the largest
  results from your calculations.

- Know at what point your variable will "roll over" and also what
  happens in the other direction e.g. (0 - 1) for unsigned arithmetic,
  or (0 - -2,147,483,648) for signed arithmetic.

- For math that requires fractions, float variables may be used, but
  be aware of their drawbacks: large size and slow computation speeds
  (the STM32 has no floating point hardware, so all floating point
  calculations have to be done in software).

- Use cast operator, e.g. ``(int)myFloat`` to convert one variable type
  to another on the fly.

Arduino Compatibility
---------------------

Since the STM32 processor on the Maple is a 32-bit machine, the int
type overflows at a much higher value on Maple than on Arduino.  In
particular, on Maple, ints do not overflow (become negative) until
they reach 2,147,483,648; on the Arduino, they overflow at 32,767.
Because of this, programs running on Maple are much less likely to run
into overflow issues.  The following table summarizes the sizes and
ranges of integer datatypes on the Maple (the ranges of ``long long``
types are approximate):

.. _lang-arithmetic-int-sizes:

.. csv-table::
   :header: Datatype, Unsigned range, Signed range, Size (bytes)
   :widths: 8, 12, 17, 8

   ``char``, 0 --- 255, -128 --- 127, 1
   ``short``, "0 --- 65,535", "-32,768 --- 32,767", 2
   ``int``,  "0 --- 4,294,967,295", "-2,147,483,648 --- 2,147,483,647", 4
   ``long``, "0 --- 4,294,967,295", "-2,147,483,648 --- 2,147,483,647", 4
   ``long long``, "0 --- 1.8*10\ :sup:`19`\ " (approx.), "-9.2*10\ :sup:`18` --- 9.2*10\ :sup:`18` (approx.)", 8


See Also
--------

- The individual sizes (in bits) of various available types are
  defined in :ref:`libmaple_types.h <libmaple-libmaple_types>`.

- :ref:`sizeof <lang-sizeof>`\ ()

.. include:: /arduino-cc-attribution.txt
