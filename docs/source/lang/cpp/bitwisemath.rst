.. highlight:: cpp

.. _lang-bitwisemath:

Bitwise Operators (``&``, ``|``, ``^``, ``~``)
==============================================

The bitwise operators perform their calculations at the bit level of
variables. They help solve a wide range of common programming
problems.

Much of the material here is adapted for Maple from an (Arduino)
`tutorial on bitwise math
<http://www.arduino.cc/playground/Code/BitMath>`_\ .  Another great
resource is the Wikipedia article on `bitwise operations
<http://en.wikipedia.org/wiki/Bitwise_operation>`_\ .

Below are descriptions and syntax for all of the operators.

.. contents:: Contents
   :local:

.. _lang-bitwisemath-and:

Bitwise AND (``&``)
-------------------

The bitwise AND operator in C++ is a single ampersand, ``&``, used
between two other integer expressions. Bitwise AND operates on each
bit position of the surrounding expressions independently, according
to this rule: if both input bits are 1, the resulting output is 1,
otherwise the output is 0. Another way of expressing this is::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  0  0  1    (operand1 & operand2) = result


On the Maple, the type ``int`` is a 32-bit value, so using ``&``
between two ``int`` expressions causes 32 simultaneous AND operations
to occur. In a code fragment like::

        int a =  92;    // in binary: 00000000000000000000000001011100
        int b = 101;    // in binary: 00000000000000000000000001100101
        int c = a & b;  // result:    00000000000000000000000001000100,
                        //    (or 68 in decimal).


Each of the 32 bits in ``a`` and ``b`` are processed using bitwise
AND, and all 32 resulting bits are stored in ``c``, resulting in the
value 1000100 in binary, which is 68 in decimal.


.. _lang-bitwisemath-or:

Bitwise OR (``|``)
------------------

The bitwise OR operator in C++ is the vertical bar symbol, ``|``. Like
the ``&`` operator, ``|`` operates independently on each bit in its
two surrounding integer expressions, but what it does is
different. The bitwise OR of two bits is 1 if either or both of the
input bits is 1, otherwise it is 0.  For example::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  1  1  1    (operand1 | operand2) = result

Here is an example of bitwise OR used in a snippet of C++ code (using
``char``, which takes up 8 bits of memory, instead of ``int``, which
uses 32)::

        char a =  92;    // in binary: 01011100
        char b = 101;    // in binary: 01100101
        char c = a | b;  // result:    01111101, or 125 in decimal.

.. _lang-bitwisemath-xor:

Bitwise XOR (``^``)
-------------------

There is a somewhat unusual operator in C++ called bitwise EXCLUSIVE
OR, also known as bitwise XOR. (In English, this is usually pronounced
"zor" or "ex-or"). The bitwise XOR operator is written using the caret
symbol, ``^``. This operator is very similar to the bitwise OR
operator ``|``, except it evaluates to 0 for a given bit position when
both of the input bits for that position are 1::

        0  0  1  1    operand1
        0  1  0  1    operand2
        ----------
        0  1  1  0    (operand1 ^ operand2) = result


Another way to look at bitwise XOR is that each bit in the result
is a 1 if the input bits are different, or 0 if they are the same.

Here is a simple example::

        int x = 12;     // binary (ignoring extra bits): 1100
        int y = 10;     // binary:                       1010
        int z = x ^ y;  // binary:                       0110, or decimal 6



The ^ operator is often used to toggle (i.e. change from 0 to 1, or 1
to 0) some of the bits in an integer expression. In a bitwise OR
operation if there is a 1 in the mask bit, that bit is inverted; if
there is a 0, the bit is not inverted and stays the same. Below is a
program to blink digital pin 13 (the LED pin on Maple)::

    // Blink Maple LED pin

    int led_pin = 13;
    int toggle = 0;

    // demo for Exclusive OR
    void setup(){
        pinMode(led_pin, OUTPUT);
    }

    void loop(){
        toggle = toggle ^ 1;
        digitalWrite(led_pin, toggle);
        delay(100);
    }

.. _lang-bitwisemath-not:

Bitwise NOT (``~``)
-------------------

The bitwise NOT operator in C++ is the tilde character ``~``. Unlike
``&`` and ``|``, the bitwise NOT operator is applied to a single
operand to its right. Bitwise NOT changes each bit to its opposite: 0
becomes 1, and 1 becomes 0. For example::

        0  1    operand1
        ----
        1  0   ~operand1 = result

Another example::

        char a = 103;    // binary:  01100111
        char b = ~a;     // binary:  10011000 = -104

You might be surprised to see a negative number like -104 as the
result of this operation. This is because the highest bit in an int
variable is the so-called "sign bit". If the highest bit is 1, the
number is interpreted as negative. This encoding of positive and
negative numbers is referred to as *two's complement*. For more
information, see the Wikipedia article on `two's
complement. <http://en.wikipedia.org/wiki/Twos_complement>`_

As an aside, it is interesting to note that (under two's complement
arithmetic) for any integer ``x``, ``~x`` is the same as ``-x-1``.

At times, the sign bit in a signed integer expression can cause
some unwanted surprises.


Uses
----

One of the most common uses of bitwise operations is to select or
manipulate a particular bit (or bits) from an integer value, often
called `bit masking
<http://en.wikipedia.org/wiki/Mask_%28computing%29>`_\ . See the
linked Wikipedia article for more information and examples.

If you really want to see bit-twiddling techniques in their full
glory, you could do much worse than to get yourself a copy of
`Hacker's Delight <http://www.hackersdelight.org/>`_\ .


See Also
--------

- :ref:`Boolean operations <lang-boolean>` (``&&``, ``||``)
- :ref:`Compound bitwise operations <lang-compoundbitwise>` (``&=``,
   ``|=``, ``^=``).

.. include:: /arduino-cc-attribution.txt
