.. _arduino-constants:

constants
=========

Constants are predefined variables in the Arduino language. They
are used to make the programs easier to read. We classify constants
in groups.



Defining Logical Levels, true and false (Boolean Constants)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There are two constants used to represent truth and falsity in the
Arduino language: **true**, and **false**.



false
-----

false is the easier of the two to define. false is defined as 0
(zero).



true
----

true is often said to be defined as 1, which is correct, but true
has a wider definition. Any integer which is *non-zero* is TRUE, in
a Boolean sense. So -1, 2 and -200 are all defined as true, too, in
a Boolean sense.



Note that the *true* and *false* constants are typed in lowercase
unlike HIGH, LOW, INPUT, & OUTPUT.



Defining Pin Levels, HIGH and LOW
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When reading or writing to a digital pin there are only two
possible values a pin can take/be-set-to: **HIGH** and **LOW**.



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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Digital pins can be used either as **INPUT** or **OUTPUT**.
Changing a pin from INPUT TO OUTPUT with pinMode() drastically
changes the electrical behavior of the pin.



Pins Configured as Inputs
-------------------------

Arduino (Atmega) pins configured as **INPUT** with pinMode() are
said to be in a high-impedance state. One way of explaining this is
that pins configured as INPUT make extremely small demands on the
circuit that they are sampling, say equivalent to a series resistor
of 100 Megohms in front of the pin. This makes them useful for
reading a sensor, but not powering an LED.



Pins Configured as Outputs
--------------------------

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



See also
--------


-  `pinMode() <http://arduino.cc/en/Reference/PinMode>`_
-  `Integer Constants <http://arduino.cc/en/Reference/IntegerConstants>`_
-  `boolean variables <http://arduino.cc/en/Reference/BooleanVariables>`_


