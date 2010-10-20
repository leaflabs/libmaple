.. _arduino-digitalread:

digitalRead()
=============

Description
-----------

Reads the value from a specified digital pin, either
`HIGH <http://arduino.cc/en/Reference/Constants>`_ or
`LOW <http://arduino.cc/en/Reference/Constants>`_.



Syntax
------

digitalRead(pin)



Parameters
----------

pin: the number of the digital pin you want to read (*int*)



Returns
-------

`HIGH <http://arduino.cc/en/Reference/Constants>`_ or
`LOW <http://arduino.cc/en/Reference/Constants>`_



Example
-------

::

     
    int ledPin = 13; // LED connected to digital pin 13
    int inPin = 7;   // pushbutton connected to digital pin 7
    int val = 0;     // variable to store the read value
    
    void setup()
    {
      pinMode(ledPin, OUTPUT);      // sets the digital pin 13 as output
      pinMode(inPin, INPUT);      // sets the digital pin 7 as input
    }
    
    void loop()
    {
      val = digitalRead(inPin);   // read the input pin
      digitalWrite(ledPin, val);    // sets the LED to the button's value
    }



Sets pin 13 to the same value as the pin 7, which is an input.



Note
----

If the pin isn't connected to anything, digitalRead() can return
either HIGH or LOW (and this can change randomly).



The analog input pins can be used as digital pins, referred to as
A0, A1, etc.



See also
--------


-  `pinMode <http://arduino.cc/en/Reference/PinMode>`_\ ()
-  `digitalWrite <http://arduino.cc/en/Reference/DigitalWrite>`_\ ()
-  `Tutorial: Digital Pins <http://arduino.cc/en/Tutorial/DigitalPins>`_


