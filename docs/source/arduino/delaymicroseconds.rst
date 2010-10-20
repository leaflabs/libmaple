.. _arduino-delaymicroseconds:

delayMicroseconds()
===================

Description
-----------

Pauses the program for the amount of time (in microseconds)
specified as parameter. There are a thousand microseconds in a
millisecond, and a million microseconds in a second.



Currently, the largest value that will produce an accurate delay is
16383. This could change in future Arduino releases. For delays
longer than a few thousand microseconds, you should use delay()
instead.



Syntax
------

delayMicroseconds(us)



Parameters
----------

us: the number of microseconds to pause (*unsigned int*)



Returns
-------

None



Example
-------

::

     
    int outPin = 8;                 // digital pin 8
    
    void setup()
    {
      pinMode(outPin, OUTPUT);      // sets the digital pin as output
    }
    
    void loop()
    {
      digitalWrite(outPin, HIGH);   // sets the pin on
      delayMicroseconds(50);        // pauses for 50 microseconds      
      digitalWrite(outPin, LOW);    // sets the pin off
      delayMicroseconds(50);        // pauses for 50 microseconds      
    }



configures pin number 8 to work as an output pin. It sends a train
of pulses with 100 microseconds period.



Caveats and Known Issues
------------------------

This function works very accurately in the range 3 microseconds and
up. We cannot assure that delayMicroseconds will perform precisely
for smaller delay-times.



As of Arduino 0018, delayMicroseconds() no longer disables
interrupts.



See also
--------


-  `millis <http://arduino.cc/en/Reference/Millis>`_\ ()
-  `micros <http://arduino.cc/en/Reference/Micros>`_\ ()
-  `delay <http://arduino.cc/en/Reference/Delay>`_\ ()


