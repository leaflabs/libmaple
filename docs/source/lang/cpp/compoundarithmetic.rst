.. highlight:: cpp

.. _lang-compoundarithmetic:

Compound Arithmetic Operators (``+=`` , ``-=``, ``*=``, ``/=``)
===============================================================

These oparators perform a mathematical operation on a variable with
another constant or variable.  These operators are just a convenient
shorthand::

    x += y;   // equivalent to the expression x = x + y;
    x -= y;   // equivalent to the expression x = x - y;
    x *= y;   // equivalent to the expression x = x * y;
    x /= y;   // equivalent to the expression x = x / y;

Here is an example::

    int x = 2;
    int y = 10;

    x += 4;          // x now contains 6
    x -= 3;          // x now contains 3
    x *= y;          // x now contains 30
    x /= 2;          // x now contains 15
    x += max(20, 6); // x now contains 35
    x -= sq(5);      // x now contains 15

Parameters
----------

**x**: a numeric variable

**y**: a numeric variable, number constant, or any other expression
that evaluates to a number (e.g. call to a function that returns a
number).

See Also
--------

- :ref:`Arithmetic operators <lang-arithmetic>`

.. include:: /arduino-cc-attribution.txt
