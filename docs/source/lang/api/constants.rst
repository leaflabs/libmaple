.. _lang-constants:

Constants
=========

Constants are like predefined variables, whose values can't
change. They are used to make the programs easier to read and modify.
This page describes the most commonly used constants.

.. contents:: Contents
   :local:

.. _lang-constants-bool:

Boolean Constants
-----------------

There are two constants used to represent truth and falsity: ``true``,
and ``false``.

.. _lang-constants-false:

false
^^^^^

``false`` is the false ``bool`` value. An integer which is 0 evaluates
to ``false`` as a boolean.

.. _lang-constants-true:

true
^^^^

``true`` is the true ``bool`` value.  As an integer, ``true`` is often
said to be 1.  This is correct in the sense that ``true`` evaluates to
1 as an integer.  However, any integer which is *non-zero* is ``true``
as a :ref:`bool <lang-booleanvariables>`. So -1, 2 and -200 are all
"true", in the sense that these numbers are treated the same as
``true`` in a boolean context.

Note that the ``true`` and ``false`` constants are typed in lowercase;
unlike e.g. ``HIGH``, ``LOW``, ``INPUT``, and ``OUTPUT`` (which are
described below).

.. _lang-pin-levels:

Pin Levels: HIGH and LOW
------------------------

When reading or writing to a digital pin there are only two possible
values a pin can be set to: ``HIGH`` and ``LOW``.

.. _lang-constants-high:

HIGH
^^^^

The meaning of ``HIGH`` (in reference to a pin) is somewhat different
depending on whether the pin is set to ``INPUT`` or ``OUTPUT``. When a
pin is configured as an ``INPUT`` (using :ref:`pinMode()
<lang-pinmode>`), and read with :ref:`digitalRead()
<lang-digitalread>`, the microcontroller will report ``HIGH`` if a
voltage of 3 volts or more is present at the pin.

When a pin is configured to ``OUTPUT`` with ``pinMode()``, and set to
``HIGH`` with :ref:`digitalWrite() <lang-digitalwrite>`, the pin is at
3.3 volts. In this state it can *source* current, e.g. light an LED
that is connected through a series resistor to ground, or to another
pin configured as an output and set to ``LOW``.

.. _lang-constants-low:

LOW
^^^

The meaning of ``LOW`` also has a different meaning depending on
whether a pin is set to ``INPUT`` or ``OUTPUT``. When a pin is
configured as an ``INPUT`` with :ref:`pinMode() <lang-pinmode>`, and
read with :ref:`digitalRead() <lang-digitalread>`, the microcontroller
will report ``LOW`` if a voltage of 2 volts or less is present at the
pin.

When a pin is configured to ``OUTPUT`` with ``pinMode()``, and set to
``LOW`` with :ref:`digitalWrite() <lang-digitalwrite>`, the
microcontroller will attempt to keep that pin's voltage at 0 V. In this
state it can *sink* current, e.g. light an LED that is connected
through a series resistor to +3.3 V, or to another pin configured as an
output, and set to ``HIGH``.

Pin Modes
---------

Digital pins can be used in a variety of modes.  The basic modes,
``INPUT`` and ``OUTPUT``, have been introduced above.  Changing a pin
from ``INPUT`` TO ``OUTPUT`` with :ref:`pinMode() <lang-pinmode>`
drastically changes the electrical behavior of the pin.

This section describes the basic digital pin modes (``INPUT`` and
``OUTPUT``) only.  For a detailed description of all possible pin
modes, see the :ref:`pinMode() <lang-pinmode>` reference page.

.. _lang-constants-input:

INPUT
^^^^^

Pins configured as ``INPUT`` are said to be in a *high-impedance
state*. One way of explaining this is that pins configured as
``INPUT`` make very few demans on circuit that they are connected
to. This makes them useful for reading a sensor, but not powering an
LED.

.. _lang-constants-output:

OUTPUT
^^^^^^

Pins configured as ``OUTPUT`` with :ref:`pinMode() <lang-pinmode>` are
said to be in a low-impedance state. This means that they can provide
a substantial amount of current to other circuits.  Pins can source
(provide positive current) or sink (provide negative current) up to 50
mA (milliamps) of current to other devices/circuits. This makes them
useful for powering LEDs, but useless for reading sensors.

Pins configured as outputs can also be damaged or destroyed if short
circuited to either ground or power supplies. The amount of current
provided by a pin is also not enough to power most relays or motors,
and some interface circuitry will be required.

.. _lang-constants-integers:

Integer Constants
-----------------

Integer constants are numbers used directly in a sketch, like
``123``. By default, an integer constant is treated as a (signed)
:ref:`int <lang-int>`, but you can change this with the U and L
modifiers (see :ref:`below <lang-constants-integers-u-l>`).  You can
specify negative numbers by putting a minus sign in front, like
``-123``.

Normally, integer constants are treated as base 10 (decimal) integers,
but special notation (formatters) may be used to enter numbers in
other bases.  These are explained in the following table:

.. list-table::
   :header-rows: 1

   * - Base
     - Example
     - Formatter
     - Comment

   * - 10 (decimal)
     - ``123``
     - None
     -

   * - 2 (binary)
     - ``0b1111011``
     - Leading "0b"
     - GCC extension; not standard C++

   * - 8 (octal)
     - ``0173``
     - Leading "0"
     - Characters 0-7 valid

   * - 16 (hexadecimal)
     - ``0x7B``
     - Leading "0x"
     - Characters 0-9, A-F (or a-f) valid

Binary constants (like ``B1111011``) for values between 0 and 255 are
supported for compatibility with Arduino only.  You shouldn't use them
in new programs.

.. _lang-constants-integers-dec:

**Decimal** is base 10. This is the common number system we learn in
school.  Integer literals without other prefixes are assumed to be in
decimal format.

For example, the decimal literal ``101`` is one hundred and one: 1×10\
:sup:`2` + 0×10\ :sup:`1` + 1×10\ :sup:`0` = 101.

.. _lang-constants-integers-bin:

**Binary** is base two. Only characters 0 and 1 are valid.  Binary
literals are indicated by the prefix ``0b``.

For example, the binary literal ``0b101`` is five: 1×2\ :sup:`2` +
0×2\ :sup:`1` + 1×2\ :sup:`0` = 5.

.. _lang-constants-integers-oct:

**Octal** is base eight. Only characters 0 through 7 are valid.  Octal
literals are indicated by the prefix ``0``.

For example, the octal literal ``0101`` is sixty five: 1×8\ :sup:`2` +
0×8\ :sup:`1` + 1×8\ :sup:`0` = 65.

.. warning:: Bugs sometimes result by (unintentionally) including a
   leading "0" before an integer literal, which makes the compiler
   treat it as an octal number.

.. _lang-constants-integers-hex:

**Hexadecimal** (or "hex") is base sixteen. Valid characters are 0
through 9 and letters A through F; A has the value 10, B is 11, up to
F, which is 15.  Hex values are indicated by the prefix ``0x``.  A-F
can be typed in upper or lower case (a-f).

For example, the hexadecimal constant ``0x101`` is two hundred fifty
seven: 1×16\ :sup:`2` + 0×16\ :sup:`1` + 1×16\ :sup:`0` = 257.

The hexadecimal constant ``0xCF2`` is three thousand, three hundred
fourteen: 12×16\ :sup:`2` + 15×16\ :sup:`1` + 2×16\ :sup:`0` = 3314.

(Remember that in hex, ``A`` means 10, and counting up, ``B``\ =11, so
``C``\ =12 and ``F``\ =15).

.. _lang-constants-integers-u-l:

U and L Suffixes
^^^^^^^^^^^^^^^^

By default, an integer constant is treated as an :ref:`int <lang-int>`
(and must be in the int type's :ref:`range limits
<lang-int-overflow>`). To specify an integer constant with another
data type, follow it with:

- a ``u`` or ``U`` to interpret the constant as an unsigned value.
  For example, ``33U`` is an :ref:`unsigned int <lang-unsignedint>`.

- an ``l`` or ``L`` to interpret the constant as a long value.  For
  example, ``100000L`` is a :ref:`long <lang-long>`.  On the Maple,
  ``long`` is just a synonym for ``int``.

- a ``ul`` or ``UL`` to do both.  For example, ``32767UL`` is an
  :ref:`unsigned long <lang-unsignedlong>`.  On the Maple, ``unsigned
  long`` is just a synonym for ``unsigned int``.

- an ``ll`` or ``LL`` to interpret the constant as a :ref:`long long
  <lang-longlong>` value.

- a ``ull`` or ``ULL`` to interpret the constant as an :ref:`unsigned
  long long <lang-unsignedlonglong>`.

.. _lang-constants-fp:

Floating-Point Constants
------------------------

A floating point constant is any number which includes a decimal
point.  For instance, ``3.0`` is a floating-point constant for the
number 3.  By default, a floating-point constant is a :ref:`double
<lang-double>`.  In order for the constant to be interpreted as a
:ref:`float <lang-float>`, you can write ``f`` directly after it.  For
example, ``3.0f`` is a floating-point constant with type ``float``.

Floating point constants can also be expressed in a variety of
scientific notation. ``E`` and ``e`` are both accepted as valid
exponent indicators.  Some examples are given in the following table:


.. list-table::
   :header-rows: 1

   * - Floating-point constant
     - Evaluates to
     - Alternate expression

   * - ``10.0``
     - 10
     -

   * - ``2.34E5``
     - 2.34×10\ :sup:`5`
     - ``234000.0``

   * - ``67e-12``
     - 67.0×10\ :sup:`-12`
     - ``0.000000000067``

.. _lang-constants-board:

Board-Specific Constants
------------------------

There are several :ref:`board-specific constants <lang-board-values>`
whose value depends on which LeafLabs board you have.  If you use
them, it will help make sure that your code will work well on all
LeafLabs boards, not just the one you have.  This will make it easier
to share your code with others.

For example, the pin number connected to the board's built-in LED is
different on the different boards, but the board-specific constant
:ref:`BOARD_LED_PIN <lang-board-values-led>` will always be the
correct value for each board.

See Also
--------

- :ref:`pinMode() <lang-pinmode>`
- :ref:`Boolean Variables <lang-booleanvariables>`
- :ref:`#define <lang-define>`
- :ref:`int <lang-int>`
- :ref:`unsigned int <lang-unsignedint>`
- :ref:`long <lang-long>`
- :ref:`unsigned long <lang-unsignedlong>`
- :ref:`long long <lang-longlong>`
- :ref:`unsigned long long <lang-unsignedlonglong>`
- :ref:`float <lang-float>`
- :ref:`double <lang-double>`
- :ref:`Board-Specific Values <lang-board-values>`

.. include:: /arduino-cc-attribution.txt
