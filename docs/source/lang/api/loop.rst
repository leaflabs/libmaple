.. highlight:: cpp

.. _lang-loop:

loop()
======

After creating a :ref:`setup() <lang-setup>` function, which
initializes your sketch, the ``loop()`` function gets called
repeatedly, allowing your program to change and respond.  Use it to
actively control your Maple board.

Example
-------

::

    int buttonPin = 38;

    // setup initializes serial and the button pin
    void setup() {
      SerialUSB.begin();
      pinMode(buttonPin, INPUT);
    }

    // loop() checks the button pin each time it executes,
    // and will print 'H' if it is pressed, 'L' otherwise
    void loop() {
      if (digitalRead(buttonPin) == HIGH) {
        SerialUSB.println('H');
      } else {
        SerialUSB.println('L');
      }

      delay(1000);
    }

See Also
--------

- :ref:`setup() <lang-setup>`


.. include:: /arduino-cc-attribution.txt
