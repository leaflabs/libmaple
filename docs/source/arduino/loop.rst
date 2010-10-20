.. _arduino-loop:

loop()
======

After creating a setup() function, which initializes and sets the
initial values, the loop() function does precisely what its name
suggests, and loops consecutively, allowing your program to change
and respond. Use it to actively control the Arduino board.



Example
~~~~~~~

::

     
    int buttonPin = 3;
    
    // setup initializes serial and the button pin
    void setup()
    {
      beginSerial(9600);
      pinMode(buttonPin, INPUT);
    }
    
    // loop checks the button pin each time,
    // and will send serial if it is pressed
    void loop()
    {
      if (digitalRead(buttonPin) == HIGH)
        serialWrite('H');
      else
        serialWrite('L');
    
      delay(1000);
    }

