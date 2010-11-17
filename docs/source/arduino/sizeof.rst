.. highlight:: cpp

.. _arduino-sizeof:

sizeof()
========

Syntax
------

::

    sizeof(type)
    sizeof(var)



Description
-----------

The ``sizeof`` operator returns the number of bytes needed to store a
value of a given type.  This can be an ordinary numeric type, like
``int``.  It can be something more complicated, like a ``struct`` or
``union``.  If the argument to ``sizeof`` is an array, it returns the
total number of bytes occupied by the array.


Examplec
--------

The ``sizeof`` operator is useful for dealing with arrays (such as
strings) where it is convenient to be able to change the size of the
array without breaking other parts of the program.

This program prints out a text string one character at a time. Try
changing the text phrase::

    char myStr[] = "this is a test";
    int i;

    void setup() {
      Serial.begin(9600);
    }

    void loop() {
      for (i = 0; i < sizeof(myStr) - 1; i++) {
        Serial.print(i, DEC);
        Serial.print(" = ");
        Serial.println(myStr[i], BYTE);
      }
    }


Note that ``sizeof`` returns the total number of bytes; this is equal
to the number of ``char``\ s only because the C++ standard guarantees
that ``sizeof(char) == 1``. So for larger variable types such as
``int``, the :ref:`for loop <arduino-for>` would look something like
this::

    for (i = 0; i < (sizeof(myInts)/sizeof(int)) - 1; i++) {
      // do something with myInts[i]
    }


.. include:: cc-attribution.txt