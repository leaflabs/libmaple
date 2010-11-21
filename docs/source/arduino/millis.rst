.. _arduino-millis:

millis()
========

Description
-----------

Returns the number of milliseconds since the Arduino board began
running the current program. This number will overflow (go back to
zero), after approximately 50 days.



Parameters
----------

None



Returns
-------

Number of milliseconds since the program started (*unsigned long*)



Example
-------

::

    unsigned long time;

    void setup(){
      Serial.begin(9600);
    }
    void loop(){
      Serial.print("Time: ");
      time = millis();
      //prints time since program started
      Serial.println(time);
      // wait a second so as not to send massive amounts of data
      delay(1000);
    }



Tip:
----

Note that the parameter for millis is an unsigned long, errors may
be generated if a programmer tries to do math with other datatypes
such as ints.



See also
--------


-  `micros <http://arduino.cc/en/Reference/Micros>`_\ ()
-  `delay <http://arduino.cc/en/Reference/Delay>`_\ ()
-  `delayMicroseconds <http://arduino.cc/en/Reference/DelayMicroseconds>`_\ ()
-  `Tutorial: Blink Without Delay <http://arduino.cc/en/Tutorial/BlinkWithoutDelay>`_



.. include:: cc-attribution.txt
