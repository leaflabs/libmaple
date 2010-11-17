.. _arduino-unsignedlong:

unsigned long
=============

Description
-----------

Unsigned long variables are extended size variables for number
storage, and store 32 bits (4 bytes). Unlike standard longs
unsigned longs won't store negative numbers, making their range
from 0 to 4,294,967,295 (2^32 - 1).



Example
-------

::

    unsigned long time;
    
    void setup()
    {
      Serial.begin(9600);
    }
    
    void loop()
    {
      Serial.print("Time: ");
      time = millis();
      //prints time since program started
      Serial.println(time);
      // wait a second so as not to send massive amounts of data
      delay(1000);
    }

Syntax
------

::

        unsigned long var = val;




-  var - your long variable name
-  val - the value you assign to that variable



See Also
--------


-  `byte <http://arduino.cc/en/Reference/Byte>`_
-  `int <http://arduino.cc/en/Reference/Int>`_
-  `unsigned int <http://arduino.cc/en/Reference/UnsignedInt>`_
-  `long <http://arduino.cc/en/Reference/Long>`_
-  `Variable Declaration <http://arduino.cc/en/Reference/VariableDeclaration>`_




.. include:: cc-attribution.txt