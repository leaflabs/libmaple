.. _arduino-digitalwrite:

digitalWrite()
==============

Description
-----------

Write a `HIGH <http://arduino.cc/en/Reference/Constants>`_ or a
`LOW <http://arduino.cc/en/Reference/Constants>`_ value to a
digital pin.



If the pin has been configured as an OUTPUT with
`pinMode <http://arduino.cc/en/Reference/PinMode>`_\ (), its voltage
will be set to the corresponding value: 5V (or 3.3V on 3.3V boards)
for HIGH, 0V (ground) for LOW.



If the pin is configured as an INPUT, writing a HIGH value with
digitalWrite() will enable an internal 20K pullup resistor (see the
`tutorial on digital pins <http://arduino.cc/en/Tutorial/DigitalPins>`_).
Writing LOW will disable the pullup. The pullup resistor is enough
to light an LED dimly, so if LEDs appear to work, but very dimly,
this is a likely cause. The remedy is to set the pin to an output
with the pinMode() function.



**NOTE:** Digital pin 13 is harder to use as a digital input than
the other digital pins because it has an LED and resistor attached
to it that's soldered to the board on most boards. If you enable
its internal 20k pull-up resistor, it will hang at around 1.7 V
instead of the expected 5V because the onboard LED and series
resistor pull the voltage level down, meaning it always returns
LOW. If you must use pin 13 as a digital input, use an external
pull down resistor.



Syntax
------

digitalWrite(pin, value)



Parameters
----------

pin: the pin number



value: `HIGH <http://arduino.cc/en/Reference/Constants>`_ or
`LOW <http://arduino.cc/en/Reference/Constants>`_



Returns
-------

none



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



Sets pin 13 to HIGH, makes a one-second-long delay, and sets the
pin back to LOW.



Note
----

The analog input pins can be used as digital pins, referred to as
A0, A1, etc.



See also
--------


-  `pinMode <http://arduino.cc/en/Reference/PinMode>`_\ ()
-  `digitalRead <http://arduino.cc/en/Reference/DigitalRead>`_\ ()
-  `Tutorial: Digital Pins <http://arduino.cc/en/Tutorial/DigitalPins>`_


