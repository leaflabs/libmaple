.. highlight:: cpp

.. _lang-increment:

Increment and Decrement Operators (``++``, ``--``)
==================================================

These operators increment (add one to) or decrement (subtract one
from) a variable.  If they come before the variable, they return its
new value; otherwise, they return its old value.

Some quick examples::

    x++;  // adds one to x, and returns the old value of x
    ++x;  // adds one to x, and returns the new value of x

    x--;   // decrement x by one and returns the old value of x
    --x;   // decrement x by one and returns the new value of x

A more extended example::

    x = 2;
    y = ++x;      // x now contains 3, y contains 3
    y = x--;      // x contains 2 again, y still contains 3

.. warning:: Be careful!  You cannot put a space in between the two
    ``+`` or ``-`` signs.  This example is broken::

        // this line won't compile (notice the extra space):
        int y = x+ +;

See Also
--------

- :ref:`lang-compoundarithmetic`

.. include:: /arduino-cc-attribution.txt
