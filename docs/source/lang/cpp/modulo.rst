.. highlight:: cpp

.. _lang-modulo:

Modulo Operator (``%``)
=======================

Calculates the `remainder <http://en.wikipedia.org/wiki/Remainder>`_
when one integer is divided by another. It is useful for keeping a
variable within a particular range (e.g.  the size of an array).

Syntax
------

::

    dividend % divisor

Parameters
----------

**dividend**: the number to be divided

**divisor**: the number to divide by

Returns
-------

The remainder of **dividend**\ /\ **divisor**\ .

Examples
--------

::

    int x;
    x = 7 % 5;   // x now contains 2
    x = 9 % 5;   // x now contains 4
    x = 5 % 5;   // x now contains 0
    x = 4 % 5;   // x now contains 4

::

    /* update one value in an array each time through a loop */

    int values[10];
    int i = 0;

    void setup() {
        // no setup necessary
    }

    void loop() {
      values[i] = analogRead(0);
      i = (i + 1) % 10;   // modulo operator makes sure i stays between 0 and 9
    }

Tip
---

The modulo operator does not work on floats.  For that, you can use
the C standard library function `fmod()
<http://sourceware.org/newlib/libm.html#fmod>`_.

See Also
--------

-  :ref:`Arithmetic <lang-arithmetic>`

.. include:: /arduino-cc-attribution.txt
