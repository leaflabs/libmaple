.. _arduino-constants:

constants
=========

Constants are predefined variables in the Arduino language. They
are used to make the programs easier to read. We classify constants
in groups.

.. contents:: Contents
   :local:

.. _arduino-constants-bool:

Boolean Constants
-----------------

There are two constants used to represent truth and falsity in the
Arduino language: **true**, and **false**.

.. _arduino-constants-false:

false
^^^^^

false is the easier of the two to define. false is defined as 0
(zero).

.. _arduino-constants-true:

true
^^^^

true is often said to be defined as 1, which is correct, but true
has a wider definition. Any integer which is *non-zero* is TRUE, in
a Boolean sense. So -1, 2 and -200 are all defined as true, too, in
a Boolean sense.


Note that the *true* and *false* constants are typed in lowercase
unlike HIGH, LOW, INPUT, & OUTPUT.


Defining Pin Levels, HIGH and LOW
---------------------------------

When reading or writing to a digital pin there are only two
possible values a pin can take/be-set-to: **HIGH** and **LOW**.

.. _arduino-constants-high:

**HIGH**



The meaning of HIGH (in reference to a pin) is somewhat different
depending on whether a pin is set to an INPUT or OUTPUT. When a pin
is configured as an INPUT with pinMode, and read with digitalRead,
the microcontroller will report HIGH if a voltage of 3 volts or
more is present at the pin.



A pin may also be configured as an INPUT with pinMode, and
subsequently made HIGH with digitalWrite, this will set the
internal 20K pullup resistors, which will *steer* the input pin to
a HIGH reading unless it is pulled LOW by external circuitry.



When a pin is configured to OUTPUT with pinMode, and set to HIGH
with digitalWrite, the pin is at 5 volts. In this state it can
*source* current, e.g. light an LED that is connected through a
series resistor to ground, or to another pin configured as an
output, and set to LOW.

.. _arduino-constants-low:

**LOW**



The meaning of LOW also has a different meaning depending on
whether a pin is set to INPUT or OUTPUT. When a pin is configured
as an INPUT with pinMode, and read with digitalRead, the
microcontroller will report LOW if a voltage of 2 volts or less is
present at the pin.



When a pin is configured to OUTPUT with pinMode, and set to LOW
with digitalWrite, the pin is at 0 volts. In this state it can
*sink* current, e.g. light an LED that is connected through a
series resistor to, +5 volts, or to another pin configured as an
output, and set to HIGH.



Defining Digital Pins, INPUT and OUTPUT
---------------------------------------

Digital pins can be used either as **INPUT** or **OUTPUT**.
Changing a pin from INPUT TO OUTPUT with pinMode() drastically
changes the electrical behavior of the pin.



Pins Configured as Inputs
^^^^^^^^^^^^^^^^^^^^^^^^^

Arduino (Atmega) pins configured as **INPUT** with pinMode() are
said to be in a high-impedance state. One way of explaining this is
that pins configured as INPUT make extremely small demands on the
circuit that they are sampling, say equivalent to a series resistor
of 100 Megohms in front of the pin. This makes them useful for
reading a sensor, but not powering an LED.



Pins Configured as Outputs
^^^^^^^^^^^^^^^^^^^^^^^^^^

Pins configured as **OUTPUT** with pinMode() are said to be in a
low-impedance state. This means that they can provide a substantial
amount of current to other circuits. Atmega pins can source
(provide positive current) or sink (provide negative current) up to
40 mA (milliamps) of current to other devices/circuits. This makes
them useful for powering LED's but useless for reading sensors.
Pins configured as outputs can also be damaged or destroyed if
short circuited to either ground or 5 volt power rails. The amount
of current provided by an Atmega pin is also not enough to power
most relays or motors, and some interface circuitry will be
required.

.. _arduino-fpconstants:

Floating-Point Constants
------------------------

Similar to integer constants, floating point constants are used to
make code more readable. Floating point constants are swapped at
compile time for the value to which the expression evaluates.



Examples:



``n = .005;``



Floating point constants can also be expressed in a variety of
scientific notation. 'E' and 'e' are both accepted as valid
exponent indicators.



::

    
    floating-point   evaluates to:      also evaluates to:
      constant 
    
       10.0              10
      2.34E5          2.34 * 10^5             234000
      67e-12        67.0 * 10^-12         .000000000067

.. _arduino-constants-integers:

Integer Constants
-----------------

Integer constants are numbers used directly in a sketch, like
``123``. By default, these numbers are treated as
`int <http://arduino.cc/en/Reference/Int>`_'s but you can change
this with the U and L modifiers (see below).



Normally, integer constants are treated as base 10 (decimal)
integers, but special notation (formatters) may be used to enter
numbers in other bases.



::

    Base               Example    Formatter        Comment

    10 (decimal)           123    none

    2 (binary)        B1111011    leading 'B'      only works with 8 bit values (0 to 255)
                                                   characters 0-1 valid

    8 (octal)             0173    leading "0"      characters 0-7 valid

    16 (hexadecimal)      0x7B    leading "0x"     characters 0-9, A-F, a-f valid

.. _arduino-constants-integers-dec:

**Decimal** is base 10. This is the common-sense math with which
you are acquainted. Constants without other prefixes are assumed to
be in decimal format.



Example:
::

    101     // same as 101 decimal   ((1 * 10^2) + (0 * 10^1) + 1)

.. _arduino-constants-integers-bin:

**Binary** is base two. Only characters 0 and 1 are valid.



Example:
::

    B101    // same as 5 decimal   ((1 * 2^2) + (0 * 2^1) + 1)

The binary formatter only works on bytes (8 bits) between 0 (B0)
and 255 (B11111111). If it is convenient to input an int (16 bits)
in binary form you can do it a two-step procedure such as:



::

    myInt = (B11001100 * 256) + B10101010;    // B11001100 is the high byte

.. _arduino-constants-integers-oct:

**Octal** is base eight. Only characters 0 through 7 are valid.  Octal
values are indicated by the prefix "0".

Example:

::

    0101    // same as 65 decimal   ((1 * 8^2) + (0 * 8^1) + 1)

Warning
It is possible to generate a hard-to-find bug by (unintentionally)
including a leading zero before a constant and having the compiler
unintentionally interpret your constant as octal.

.. _arduino-constants-integers-hex:

**Hexadecimal (or hex)** is base sixteen. Valid characters are 0
through 9 and letters A through F; A has the value 10, B is 11, up
to F, which is 15. Hex values are indicated by the prefix "0x".
Note that A-F may be syted in upper or lower case (a-f).



Example:

::

    0x101   // same as 257 decimal   ((1 * 16^2) + (0 * 16^1) + 1)

.. _arduino-constants-integers-u-l:

U & L formatters
^^^^^^^^^^^^^^^^

By default, an integer constant is treated as an
`int <http://arduino.cc/en/Reference/Int>`_ with the attendant
limitations in values. To specify an integer constant with another
data type, follow it with:




-  a 'u' or 'U' to force the constant into an unsigned data format.
   Example: ``33u``
-  a 'l' or 'L' to force the constant into a long data format.
   Example: ``100000L``
-  a 'ul' or 'UL' to force the constant into an unsigned long
   constant. Example: ``32767ul``




See also
--------


-  `pinMode() <http://arduino.cc/en/Reference/PinMode>`_
-  `Integer Constants <http://arduino.cc/en/Reference/IntegerConstants>`_
-  `boolean variables <http://arduino.cc/en/Reference/BooleanVariables>`_
-  `#define <http://arduino.cc/en/Reference/Define>`_
-  `byte <http://arduino.cc/en/Reference/Byte>`_
-  `int <http://arduino.cc/en/Reference/Int>`_
-  `unsigned int <http://arduino.cc/en/Reference/UnsignedInt>`_
-  `long <http://arduino.cc/en/Reference/Long>`_
-  `unsigned long <http://arduino.cc/en/Reference/UnsignedLong>`_
