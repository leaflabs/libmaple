.. highlight:: cpp

.. _libs-servo:

Servo
=====

This documents the Servo library for controlling RC servomotors.  It
is implemented as a thin layer over the built-in :ref:`timer
peripherals <timers>`.

You can use this library in the :ref:`IDE <ide>` by choosing the Servo
item under the Sketch > Import Library... menu.

If you are using the :ref:`Unix toolchain <unix-toolchain>`, the
library is located in the ``/libraries/Servo/`` :ref:`libmaple`
directory.

.. contents:: Contents
   :local:

Servo Class Reference
---------------------

You can construct a Servo object by including the declaration ::

     Servo servo;

in your sketch.  This will create a Servo object called ``servo``.
You can then use any of its methods; for instance, to control a
servomotor attached to pin 9, you could write ::

     servo.attach(9);

.. doxygenclass:: Servo
   :members:

Arduino Compatibility
---------------------

The Servo class provides a public interface identical to the Arduino
version's documented functionality (as of Arduino 0021), so in most
cases, this library will be a drop-in replacement.

However, there are some differences, essentially at the level of
implementation details.

The major difference is that while the Arduino implementation drives
servos with "bit-banged" PWM (in the sense that timer interrupt
handlers are used to manually toggle pins), the Maple implementation
uses :ref:`timers <timers>` to drive the PWM directly.

Consequently, **the Maple implementation only allows Servo instances
to attach to pins that support PWM**.

To determine if a pin supports PWM, you can either check if "PWM"
appears next to its number on your board's silkscreen, or look for it
in the list of :ref:`boardPWMPins <lang-board-values-pwm-pins>` in
your board's :ref:`hardware documentation <index-boards>`.

RC Servos expect a pulse approximately every 20ms.  In the Maple
implementation, :ref:`periods <lang-hardwaretimer-setperiod>` are set
for entire timers, rather than individual channels.  Thus,
``attach()``\ ing a Servo to a pin can interfere with other pins
associated with the same timer\ [#fard-servo]_.

Because of this, we recommend connecting multiple servomotors to pins
which share a timer, in order to keep as many timers free for other
purposes as possible.  Consult your board's :ref:`Timer Pin Map
<gpio-pin-maps>` to match up pins and timer channels.

And here's some fine print:

- Although it is not publicly documented to do so, the Arduino
  implementation of `attach()
  <http://arduino.cc/en/Reference/ServoAttach>`_ returns the timer
  channel associated with the newly-attached pin, or 0 on failure (as
  of Arduino 0021).  The Maple implementation returns :ref:`true
  <lang-constants-true>` on success, and :ref:`false
  <lang-constants-false>` on failure (and this is its documented
  behavior).

- In another bit of undocumented behavior, the Arduino implementation
  of write() also treats its argument as an angle or a pulse width
  depending on its value.  This is a bad idea, and we don't do it.

.. rubric:: Footnotes

.. [#fard-servo] The Arduino implementation also captures timer
   channels in groups as more Servo objects are attached, but the
   details of which channels have their periods reset when are
   slightly different.
