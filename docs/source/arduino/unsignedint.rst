.. _arduino-unsignedint:

unsigned int
============

Description
-----------

Unsigned ints (unsigned integers) are the same as ints in that they
store a 2 byte value. Instead of storing negative numbers however
they only store positive values, yielding a useful range of 0 to
65,535 (2^16) - 1).



The difference between unsigned ints and (signed) ints, lies in the
way the highest bit, sometimes refered to as the "sign" bit, is
interpreted. In the Arduino int type (which is signed), if the high
bit is a "1", the number is interpreted as a negative number, and
the other 15 bits are interpreted with
`2's complement math. <http://en.wikipedia.org/wiki/2's_complement>`_



Example
-------

::

        unsigned int ledPin = 13;



Syntax
------

::

         unsigned int var = val;




-  var - your unsigned int variable name
-  val - the value you assign to that variable



Coding Tip
----------

When variables are made to exceed their maximum capacity they "roll
over" back to their minimum capacitiy, note that this happens in
both directions



::

       unsigned int x
       x = 0;
       x = x - 1;       // x now contains 65535 - rolls over in neg direction
       x = x + 1;       // x now contains 0 - rolls over



See Also
--------


-  `byte <http://arduino.cc/en/Reference/Byte>`_
-  `int <http://arduino.cc/en/Reference/Int>`_
-  `long <http://arduino.cc/en/Reference/Long>`_
-  `unsigned long <http://arduino.cc/en/Reference/UnsignedLong>`_
-  `Variable Declaration <http://arduino.cc/en/Reference/VariableDeclaration>`_




.. include:: cc-attribution.txt