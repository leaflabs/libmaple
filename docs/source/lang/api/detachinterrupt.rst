.. _lang-detachinterrupt:

detachInterrupt()
=================

Used to disable an interrupt specified with
:ref:`lang-attachinterrupt`\ .

Library Documentation
---------------------

.. FIXME [Breathe] once we can get the correct detachInterupt(),
.. replace with doxygenfunction.

.. cpp:function:: void detachInterrupt(uint8 pin)

   Disable any registered external interrupt on the given pin.

   *Parameters*

       - ``pin`` Maple pin number

Arduino Compatibility
---------------------

There is one important difference between the Maple version of
detachInterrupt and the Arduino version.  On the Maple, the argument
to ``detachInterrupt()`` is the *pin* on which the interrupt is
attached, while on the Arduino, the argument is the *interrupt
number*, which is different from the pin the interrupt is enabled on.

If you're calling this function, you've already called
:ref:`lang-attachinterrupt` to set up your interrupt handler, so
just call ``detachInterrupt()`` with the same pin argument you gave to
``attachInterrupt()``.

See Also
--------

- :ref:`attachInterrupt() <lang-attachInterrupt>`
- :ref:`external-interrupts`

.. include:: /arduino-cc-attribution.txt
