.. _gpio:

GPIO
====

Each LeafLabs board comes with ready-to-use General Purpose
Input/Output (GPIO) pins, which are numbered starting from zero.
These numbers are listed on your board's silkscreen, next to where the
pin is broken out to a header.  Many pins may additionally be used for
special features or interfacing with other hardware.

.. contents:: Contents
   :local:

.. _gpio-modes:

GPIO Modes
----------

Each GPIO pin can be configured using :ref:`lang-pinmode` to behave in
a number of ways: as a digital output pin, as an analog input pin,
etc.

A :ref:`WiringPinMode <lang-pinmode-wiringpinmode>` value specifies
the complete set of possible configurations; not every pin can have
all of these modes.  For example, on the Maple, pin 15 may have mode
``INPUT_ANALOG``, but not ``PWM``.  See your board's :ref:`pin maps
<gpio-pin-maps>` and its silkscreen for more information on what
functionality is available on each pin.

Function Reference
------------------

- :ref:`lang-pinmode`

- :ref:`lang-digitalread`

- :ref:`lang-digitalwrite`

- :ref:`lang-analogread`

- :ref:`lang-pwmwrite` (Maple's equivalent to ``analogWrite()``; see
  :ref:`lang-analogwrite` for differences from the Arduino version).

.. _gpio-ports:

GPIO Ports
----------

Normally, you'll interact with pins using just their number (or a
constant like :ref:`BOARD_LED_PIN <lang-board-values-led>` which
stands for a number).  However, behind the scenes, the STM32
microcontroller on your board separates the pins into groups called
*GPIO ports*.  Each GPIO port is given a letter, so for example,
there's GPIO port A, port B, and so on\ [#fnumports]_.  The pins on a
GPIO port are given *bit numbers*, which go from 0 to 15.  In ST's
documentation, a pin is given by the letter "P", followed by its port
letter and bit number.  For instance, "PA4" is GPIO port A, bit 4.

.. _gpio-pin-maps:

Pin Maps
--------

Part of :ref:`Maple IDE's <ide>` job is to convert normal pin numbers
into the corresponding GPIO port and bit when you call functions like
:ref:`lang-pinmode`.  It does this using a *pin map*, which lists the
GPIO port and bit for each pin number.  The GPIO documentation for
your board includes its pin map, which also lists the other
peripherals by pin number:

.. TODO [0.0.12] Native link

* :ref:`Maple <maple-gpios>`
* :ref:`Maple RET6 Edition <maple-ret6-gpios>`
* :ref:`Maple Mini <maple-mini-gpios>`

.. * :ref:`Maple Native <maple-native-gpios>`

.. _gpio-5v-tolerant:

The current and voltage limitations were determined using the STM32
datasheets.  In particular, only some GPIO pins are **5V tolerant**,
which means that applying 5 volts to a pin and reading it as input or
allowing it to drain to ground will not damage that pin.  Connecting a
voltage higher than 3.3V to a non-5V tolerant pin may damage your
board.

.. _gpio-recommended-reading:

Recommended Reading
-------------------

* ST Documentation for the STM32F103 series of microcontrollers:

  * `Reference Manual RM0008
    <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf>`_
    (PDF); general, definitive resource for STM32F1 line.
  * `Programming Manual PM0056
    <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/PROGRAMMING_MANUAL/CD00228163.pdf>`_
    (PDF); assembly language and register reference.

.. rubric:: Footnotes

.. [#fnumports] The total number of GPIO ports depends on what board
   you have.  For example, Maple Mini has three: ports A, B, and C.
   Maple Native has seven: ports A through G.
