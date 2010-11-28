.. _lang-micros:

micros()
========

Description
-----------

Returns the number of microseconds since the Arduino board began
running the current program. This number will overflow (go back to
zero), after approximately 70 minutes. On 16 MHz Arduino boards
(e.g. Duemilanove and Nano), this function has a resolution of four
microseconds (i.e. the value returned is always a multiple of
four). On 8 MHz Arduino boards (e.g. the LilyPad), this function
has a resolution of eight microseconds.



*Note*: there are 1,000 microseconds in a millisecond and 1,000,000
microseconds in a second.



Parameters
----------

None



Returns
-------

Number of microseconds since the program started (*unsigned long*)



Example
-------

::

    unsigned long time;

    void setup(){
      Serial.begin(9600);
    }
    void loop(){
      Serial.print("Time: ");
      time = micros();
      //prints time since program started
      Serial.println(time);
      // wait a second so as not to send massive amounts of data
      delay(1000);
    }



See also
--------


-  `millis <http://arduino.cc/en/Reference/Millis>`_\ ()
-  `delay <http://arduino.cc/en/Reference/Delay>`_\ ()
-  `delayMicroseconds <http://arduino.cc/en/Reference/DelayMicroseconds>`_\ ()



.. include:: cc-attribution.txt
