.. highlight:: cpp

.. _lang-char:

``char``
========

The ``char`` type stores a 1-byte character value (or integer with
value from -128 to 127).  Character literals are written in single
quotes, like this: ``'A'`` (for multiple characters - strings - use
double quotes: ``"ABC"``).

Just like everything else on a computer, characters are stored as
numbers. You can see the specific encoding in the `ASCII chart
<http://en.wikipedia.org/wiki/ASCII#ASCII_printable_characters>`_\
. This means that it is possible to do arithmetic on characters, in
which the ASCII value of the character is used (e.g. ``'A' + 1`` has the
decimal value 66, since the ASCII value of the capital letter A in
decimal is 65).  See the :ref:`Serial.println()
<lang-serial-println>` documentation for more information about how
characters are converted into numbers.

The ``char`` datatype is a signed type, meaning that it encodes
numbers from -128 to 127.  For an unsigned type, which stores values
from 0 to 255, just use the type ``unsigned char`` (two words).

Example
-------

::

      // The following two lines are equivalent, using the ASCII
      // character encoding:
      char c = 'A';
      char c = 65;

See Also
--------

- :ref:`lang-int`
- :ref:`lang-array` (a string is just an array of ``char``\ s)
- :ref:`Serial.println() <lang-serial-println>`

.. include:: cc-attribution.txt
