.. _arduino-nointerrupts:

noInterrupts()
==============

Description
-----------

Disables interrupts (you can re-enable them with interrupts()).
Interrupts allow certain important tasks to happen in the
background and are enabled by default. Some functions will not work
while interrupts are disabled, and incoming communication may be
ignored. Interrupts can slightly disrupt the timing of code,
however, and may be disabled for particularly critical sections of
code.



Parameters
----------

None.



Returns
-------

None.



Example
-------

::

    void setup() {}
    
    void loop()
    {
      noInterrupts();
      // critical, time-sensitive code here
      interrupts();
      // other code here
    }



See Also
--------


-  `interrupts <http://arduino.cc/en/Reference/Interrupts>`_\ ()




.. include:: cc-attribution.txt