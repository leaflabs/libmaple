.. highlight:: cpp

.. _compatibility:

=============================
 Maple-Arduino Compatibility
=============================

.. contents:: Contents
   :local:

Overview
--------

The biggest difference between the Maple and most Arduino boards is
that the Maple uses a 32-bit ARM Cortex-M3 architecture chip while the
Arduinos have 8-bit Atmel AVR chips. The different instruction set
means that machine code (executable binary programs) is incompatible
between the two, and a different compiler (actually just a different
version of `gcc <http://gcc.gnu.org/>`_) is required. The compiler for
the regular Arduino IDE is the popular :command:`avr-gcc` package; the
compiler for the Maple version of the IDE is CodeSourcery's edition of
gcc for the ARM EABI target (:command:`arm-non-eabi-gcc`).

The bitwidth of the processor means that the Maple can process 32-bit
operations (like adding two 32-bit integers) in a single instruction,
while an Arduino processor would have to split up large operations
into several smaller ones. In a lot of cases 8-bit operations are
plenty (integers 0-255, single characters of text, etc.), but if
you're dealing with higher resolution data, the speed up could be
significant. A trade-off is that code could be larger as well; program
instructions and memory locations can be up to 32-bits each, which in
the worst case would quadruple program size. In reality, the removal
of extra instructions and fancy packing together of simple
instructions means that programs aren't much larger (or are even
smaller).

Header Numbering and Incompatibilities
--------------------------------------

The numbering of headers is different; on the Maple each GPIO has a
unique number: D0, D1, D2, all the way up to D37 (actually, there are
:ref:`a few more <jtag>`...). On the Arduino, the analog pins are
numbered separately (A0-A5) from the digital pins (D0\ -D13).

The incompatible hardware differences are:

* |i2c| port: on most Arduinos, the |i2c| port is Analog Input
  4 (SDA) and Analog Input 5 (SCL); on the Maple, |i2c| port 1 is D5
  (SCL) and D9 (SDA), and |i2c| port 2 is D29 (SCL) and D30 (SDA).

  It should be possible to skywire, sacrificing signal quality (due to
  increased capacitance). Alternatively, |i2c| can be bit-banged
  reasonably well in software. This peripheral could potentially be
  rerouted internally, but we haven't looked into it.

* :ref:`PWM <pwm>` on D10: all the other standard Arduino PWM headers have PWM
  functionality on the Maple (D2,D3,D6,D9,D11), but not D10. We did
  our best! It may be possible to reroute this peripheral internally
  using low level configuration, but we haven't looked in to it.

* No External Voltage Reference: The Arduino has an Aref pin which
  allows the use of an external ADC voltage reference; the Maple has
  an extra GPIO pin (14) with PWM capability in this spot, and does
  not allow an external voltage reference to be configured.

* EEPROM: the Maple does not have any internal EEPROM. This
  functionality can be emulated with regular persistent flash memory,
  or with an external EEPROM chip.

* ISP Programming: the Maple does not use an ISP/ICSP bus for
  debugging; it uses :ref:`JTAG <jtag>`.


Software Language/Library Changes
---------------------------------

With :ref:`one notable exception <language-no-word>`, the entire
Arduino language is supported.  However, there are some subtle
differences, most of which are improvements:

* 32-bit integers: many standard functions either expect or return
  full 32-bit (4 byte) integer values instead of the regular 16-bit (2
  byte) Arduino values.

* `pinMode()`_ types: any :ref:`GPIO <gpio>` (including analog pins)
  can be configured into one of the following modes with a single call
  to `pinMode()`_: ``OUTPUT``, ``OUTPUT_OPEN_DRAIN``,
  ``INPUT_FLOATING``, ``INPUT_PULLUP``,
  ``INPUT_PULLDOWN``. Additionally, the PWM and Analog Input pins can
  be configured as ``INPUT_ANALOG`` and ``PWM`` respectively. See the
  :ref:`GPIO documentation <gpio>` for more information.

  .. TODO: reference libmaple docs above when they're done

* Serial1 syntax: like the `Arduino Mega
  <http://arduino.cc/en/Main/ArduinoBoardMega>`_, the Maple has
  multiple USART ports.  By default, Serial is not mapped to any of
  them, use ``Serial1`` through ``Serial3`` instead.

  .. TODO: reference libmaple docs for Serial[n] above when they're done

* 16-bit :ref:`PWM <pwm>`: Arduino boards support 8-bit PWM, which
  means that calls to `analogWrite()`_ take values between 0 (always
  off) and 255 (always on).  The Maple supports 16-bit PWM, so the
  corresponding values should be between 0 (always off) and 65535
  (always on).

* 12-bit :ref:`ADC <adc>`: Arduino boards support 10-bit ADC, which
  means that calls to `analogRead()`_ will return values between 0 and
  1023.  The Maple supports 12-bit ADC, so the same call will instead
  return values between 0 and 4095.


.. class:: ported-feature

I am supported!

This should be ordinary

.. class:: non-ported-feature

I can't do it :(

Also ordinary

.. class:: partly-ported-feature

I sorta work

And I am also ordinary

Stub (unfinished)

