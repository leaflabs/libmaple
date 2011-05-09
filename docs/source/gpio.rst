.. _gpio:

GPIO
====

Each LeafLabs board comes with ready-to-use General Purpose
Input/Output (GPIO) pins, which are numbered starting from zero.
These numbers are listed on your board's silkscreen, next to where the
pin is broken out to a header.  Many pins may additionally be used for
special features or peripheral functions.

.. contents:: Contents
   :local:

.. _gpio-pin-maps:

Pin Maps
--------

The hardware documentation for your board lists each pin's
capabilities, by pin number:

.. TODO [0.1.0] Uncomment Mini and Native GPIO links

* :ref:`Maple <maple-gpios>`
* :ref:`Maple RET6 Edition <maple-ret6-gpios>`

.. * :ref:`Maple Mini <maple-mini-gpios>`
.. * :ref:`Maple Native <maple-native-gpios>`

The current and voltage limitations were determined using the STM32
datasheets.  In particular, only some GPIO pins are **5V tolerant**,
which means that applying 5 volts to a pin and reading it as input or
allowing it to drain to ground will not damage that pin.  Connecting a
voltage higher than 3.3V to a non-5V tolerant pin may damage your
board.

.. _gpio-modes:

GPIO Modes
----------

Each of the GPIO pins on a Maple board may be configured using
pinMode() to behave in a number of ways: as a digital output pin,
or as an analog input pin, etc., depending on the particular pin.

A ``WiringPinMode`` value specifies the complete set of possible
configurations; not every pin can have all of these modes.  For
example, on the Maple, pin 15 may have mode ``INPUT_ANALOG``, but not
``PWM``.  See your :ref:`board's pin maps <gpio-pin-maps>` and its
silkscreen for more information on what functionality is available on
each pin.

.. doxygenenum:: WiringPinMode

Function Reference
------------------

- :ref:`pinMode() <lang-pinmode>`

- :ref:`digitalRead() <lang-digitalread>`

- :ref:`digitalWrite() <lang-digitalwrite>`

- :ref:`analogRead() <lang-analogread>`

- :ref:`pwmWrite() <lang-pwmwrite>` (Maple's equivalent to
  ``analogWrite()``; see the :ref:`analogWrite() reference
  <lang-analogwrite>` for differences from the Arduino version).

.. _gpio-recommended-reading:

Recommended Reading
-------------------

* ST Documentation for the STM32F103 series of microcontrollers:

  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)

  * `Programming Manual
    <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_
    (PDF; assembly language and register reference)

