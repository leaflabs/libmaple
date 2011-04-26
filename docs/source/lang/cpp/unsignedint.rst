.. highlight:: cpp

.. _lang-unsignedint:

``unsigned int``
================

An ``unsigned int`` (unsigned integer) is the same as an :ref:`int
<lang-int>` in that it stores a 4 byte integer value.  However,
Instead of storing both negative and positive numbers, an ``unsigned
int`` can only store nonnegative values, yielding a range of 0 to
4,294,967,295 (the positive value is 2^32 - 1).

The difference between an ``unsigned int`` and a (signed) ``int`` lies
in the way the highest bit, sometimes referred to as the "sign" bit,
is interpreted.  In the case of the Maple ``int`` type (which is
signed), if the high bit is a "1", the number is interpreted as a
negative number, using a technique known as `two's complement math
<http://en.wikipedia.org/wiki/Two%27s_complement#Explanation>`_.  The
bits in an an ``unsigned int`` are interpreted according to the usual
rules for converting `binary to decimal
<http://en.wikipedia.org/wiki/Binary_numeral_system#Counting_in_binary>`_.

An ``unsigned int`` is subject to the same :ref:`overflow issues
<lang-int-overflow>` as a regular ``int``; the only difference is
that an ``unsigned int`` will "underflow" at 0, and "overflow" at
4,294,967,295.  Here is some example code which illustrates this::

       unsigned int x;
       x = 0;
       x--; // x now contains 4,294,967,295; rolled over "left to right"
       x++; // x now contains 0; rolled over "right to left"

.. _lang-unsignedlong:

The ``unsigned long`` type is a synonym for ``unsigned int``.

Here is an example of declaring an ``unsigned int`` variable named
``ledPin``, then giving it value 13::

        unsigned int ledPin = 13;

The general syntax for declaring an ``unsigned int`` variable named
``var``, then giving it value ``val``, looks like::

         unsigned int var = val;

See Also
--------

-  :ref:`int <lang-int>`
-  :ref:`char <lang-char>`
-  :ref:`unsigned char <lang-unsignedchar>`
-  :ref:`long long <lang-longlong>`
-  :ref:`unsigned long long <lang-unsignedlonglong>`
-  :ref:`Integer Constants <lang-constants-integers>`
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt
