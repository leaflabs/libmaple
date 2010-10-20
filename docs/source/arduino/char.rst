.. _arduino-char:

char
====

Description
-----------

A data type that takes up 1 byte of memory that stores a character
value. Character literals are written in single quotes, like this:
'A' (for multiple characters - strings - use double quotes:
"ABC").



Characters are stored as numbers however. You can see the specific
encoding in the
`ASCII chart <http://arduino.cc/en/Reference/ASCIIchart>`_. This
means that it is possible to do arithmetic on characters, in which
the ASCII value of the character is used (e.g. 'A' + 1 has the
value 66, since the ASCII value of the capital letter A is 65). See
`Serial.println <http://arduino.cc/en/Serial/Println>`_ reference
for more on how characters are translated to numbers.



The char datatype is a signed type, meaning that it encodes numbers
from -128 to 127. For an unsigned, one-byte (8 bit) data type, use
the *byte* data type.



Example
-------

::

      char myChar = 'A';
      char myChar = 65;      // both are equivalent



See also
--------


-  `byte <http://arduino.cc/en/Reference/Byte>`_
-  `int <http://arduino.cc/en/Reference/Int>`_
-  `array <http://arduino.cc/en/Reference/Array>`_
-  `Serial.println <http://arduino.cc/en/Serial/Println>`_

