.. _arduino-delay:

delay()
=======

Description
-----------

Pauses the program for the amount of time (in miliseconds)
specified as parameter. (There are 1000 milliseconds in a second.)



Syntax
------

delay(ms)



Parameters
----------

ms: the number of milliseconds to pause (*unsigned long*)



Returns
-------

nothing



Example
-------

::

    int ledPin = 13;                 // LED connected to digital pin 13
    
    void setup()
    {
      pinMode(ledPin, OUTPUT);      // sets the digital pin as output
    }
    
    void loop()
    {
      digitalWrite(ledPin, HIGH);   // sets the LED on
      delay(1000);                  // waits for a second
      digitalWrite(ledPin, LOW);    // sets the LED off
      delay(1000);                  // waits for a second
    }



Caveat
------

While it is easy to create a blinking LED with the delay()
function, and many sketches use short delays for such tasks as
switch debouncing, the use of delay() in a sketch has significant
drawbacks. No other reading of sensors, mathematical calculations,
or pin manipulation can go on during the delay function, so in
effect, it brings most other activity to a halt. For alternative
approaches to controlling timing see the
`millis() <http://arduino.cc/en/Reference/Millis>`_ function and
the sketch sited below. More knowledgeable programmers usually
avoid the use of delay() for timing of events longer than 10's of
milliseconds unless the Arduino sketch is very simple.



Certain things *do* go on while the delay() function is controlling
the Atmega chip however, because the delay function does not
disable interrupts. Serial communication that appears at the RX pin
is recorded, PWM
(`analogWrite <http://arduino.cc/en/Reference/AnalogWrite>`_)
values and pin states are maintained, and
`interrupts <http://arduino.cc/en/Reference/AttachInterrupt>`_ will
work as they should.



See also
--------


-  `millis <http://arduino.cc/en/Reference/Millis>`_\ ()
-  `micros <http://arduino.cc/en/Reference/Micros>`_\ ()
-  `delayMicroseconds <http://arduino.cc/en/Reference/DelayMicroseconds>`_\ ()
-  `Blink Without Delay <http://arduino.cc/en/Tutorial/BlinkWithoutDelay>`_
   example

