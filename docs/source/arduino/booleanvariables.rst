.. _arduino-booleanvariables:

boolean
=======

A **boolean** holds one of two values,
`true <http://arduino.cc/en/Reference/Constants>`_ or
`false <http://arduino.cc/en/Reference/Constants>`_. (Each boolean
variable occupies one byte of memory.)



Example
-------

::

    int LEDpin = 5;       // LED on pin 5
    int switchPin = 13;   // momentary switch on 13, other side connected to ground
    
    boolean running = false;
    
    void setup()
    {
      pinMode(LEDpin, OUTPUT);
      pinMode(switchPin, INPUT);
      digitalWrite(switchPin, HIGH);      // turn on pullup resistor
    }
    
    void loop()
    {
      if (digitalRead(switchPin) == LOW)
      {  // switch is pressed - pullup keeps pin high normally
        delay(100);                        // delay to debounce switch
        running = !running;                // toggle running variable
        digitalWrite(LEDpin, running)      // indicate via LED
      }
    }
    
    
    



See also
--------


-  `constants <http://arduino.cc/en/Reference/Constants>`_
-  `boolean operators <http://arduino.cc/en/Reference/Boolean>`_
-  `Variable Declaration <http://arduino.cc/en/Reference/VariableDeclaration>`_


