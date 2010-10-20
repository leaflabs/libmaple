.. _arduino-interrupts:

interrupts()
============

Description
-----------

Re-enables interrupts (after they've been disabled by
`noInterrupts <http://arduino.cc/en/Reference/NoInterrupts>`_\ ()).
Interrupts allow certain important tasks to happen in the
background and are enabled by default. Some functions will not work
while interrupts are disabled, and incoming communication may be
ignored. Interrupts can slightly disrupt the timing of code,
however, and may be disabled for particularly critical sections of
code.



Parameters
----------

None



Returns
-------

None



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


-  `noInterrupts <http://arduino.cc/en/Reference/NoInterrupts>`_\ ()
-  `attachInterrupt <http://arduino.cc/en/Reference/AttachInterrupt>`_\ ()
-  `detachInterrupt <http://arduino.cc/en/Reference/DetachInterrupt>`_\ ()


