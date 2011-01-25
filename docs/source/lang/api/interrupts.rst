.. highlight:: cpp

.. _lang-interrupts:

interrupts()
============

Re-enables interrupts (after they've been disabled by
:ref:`noInterrupts() <lang-nointerrupts>`).  Interrupts allow certain
important tasks to happen in the background, and certain interrupts
are enabled by default.

Some functions will not work while interrupts are disabled, and both
incoming and outgoing communication may be ignored. Interrupts can
slightly disrupt the timing of code, however, and may be disabled for
particularly critical sections of code.

Library Documentation
---------------------

.. doxygenfunction:: interrupts

Example
-------

::

    void setup() {}

    void loop() {
      noInterrupts();
      // critical, time-sensitive code here
      interrupts();
      // other code here
    }

See Also
--------

- :ref:`noInterrupts() <lang-nointerrupts>`
- :ref:`attachInterrupt() <lang-attachinterrupt>`
- :ref:`detachInterrupt() <lang-detachinterrupt>`
- :ref:`Timers reference <timers>`
- :ref:`Timer API <lang-hardwaretimer>`
- :ref:`External interrupts <external-interrupts>`

.. include:: /lang/cc-attribution.txt
