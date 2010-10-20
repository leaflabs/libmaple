.. _arduino-volatile:

volatile keyword
================

volatile is a keyword known as a variable *qualifier*, it is
usually used before the datatype of a variable, to modify the way
in which the compiler and subsequent program treats the variable.



Declaring a variable volatile is a directive to the compiler. The
compiler is software which translates your C/C++ code into the
machine code, which are the real instructions for the Atmega chip
in the Arduino.



Specifically, it directs the compiler to load the variable from RAM
and not from a storage register, which is a temporary memory
location where program variables are stored and manipulated. Under
certain conditions, the value for a variable stored in registers
can be inaccurate.



A variable should be declared volatile whenever its value can be
changed by something beyond the control of the code section in
which it appears, such as a concurrently executing thread. In the
Arduino, the only place that this is likely to occur is in sections
of code associated with interrupts, called an interrupt service
routine.



Example
-------

::

    // toggles LED when interrupt pin changes state
    
    int pin = 13;
    volatile int state = LOW;
    
    void setup()
    {
      pinMode(pin, OUTPUT);
      attachInterrupt(0, blink, CHANGE);
    }
    
    void loop()
    {
      digitalWrite(pin, state);
    }
    
    void blink()
    {
      state = !state;
    }



See also
--------


-  `AttachInterrupt <http://arduino.cc/en/Reference/AttachInterrupt>`_


