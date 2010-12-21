.. highlight:: cpp

.. _lang-nointerrupts:

noInterrupts()
==============

Description
-----------

Disables interrupts.  Interrupts allow certain important tasks to
happen in the background and are enabled by default. Some functions
will not work while interrupts are disabled, and incoming
communication may be ignored. Interrupts can slightly disrupt the
timing of code, however, and may be disabled for particularly critical
sections of code.

Library Documentation
---------------------

.. doxygenfunction:: noInterrupts

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

- :ref:`interrupts() <lang-interrupts>`
- :ref:`attachInterrupt() <lang-attachinterrupt>`
- :ref:`detachInterrupt() <lang-detachinterrupt>`
- :ref:`Timers reference <timers>`
- :ref:`Timer API <lang-hardwaretimer>`
- :ref:`External interrupts <external-interrupts>`

.. include:: /lang/cc-attribution.txt
