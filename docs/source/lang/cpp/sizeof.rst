.. highlight:: cpp

.. _lang-sizeof:

``sizeof()``
============

The ``sizeof`` operator on the Maple returns the number of bytes
needed to store a value of a given type\ [#fcharsize]_.  This can be
an ordinary numeric type, like ``int``.  It can be something more
complicated, like a ``struct`` or ``union``.  If the argument to
``sizeof`` is an array, it returns the total number of bytes occupied
by the array.

The general syntax looks like this::

    sizeof(type)
    sizeof(var)

Example
-------

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


Note that ``sizeof`` returns the total number of bytes. So for larger
variable types such as ``int``, the :ref:`for loop <lang-for>`
would look something like this::

    for (i = 0; i < (sizeof(myInts)/sizeof(int)) - 1; i++) {
      // do something with myInts[i]
    }

.. rubric:: Footnotes

.. [#fcharsize] Technically (and pedantically) speaking, ``sizeof``
   returns a multiple of the number of bits a ``char`` occupies in
   memory.  However, on the Maple (this goes for most C++
   implementations), a ``char`` occupies 8 bits = 1 byte.  All the C++
   standard guarantees, however, is that a ``char`` occupies at
   *least* 8 bits.

.. include:: /arduino-cc-attribution.txt

