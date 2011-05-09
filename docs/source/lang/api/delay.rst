.. highlight:: cpp

.. _lang-delay:

delay()
=======

Pauses the program for at least a given number of milliseconds. (There
are 1000 milliseconds in a second.)

Library Documentation
---------------------

.. doxygenfunction:: delay


Discussion
----------

While it is easy to create a blinking LED with the ``delay()``
function, and many sketches use short delays for such tasks as switch
debouncing, the use of ``delay()`` in a sketch has significant
drawbacks.  No other reading of sensors, mathematical calculations, or
pin manipulation can go on during the delay function, so in effect, it
brings most other activity to a halt. For alternative approaches to
controlling timing see the :ref:`millis() <lang-millis>` function
and the "Blink Without Delay" sketch cited :ref:`below
<lang-delay-seealso>`\ . More knowledgeable programmers usually
avoid the use of ``delay()`` for timing of events longer than tens of
milliseconds, unless the sketch is very simple.

Certain things *do* go on while the ``delay()`` function is
controlling the STM32 chip, however, because the delay function does
not disable interrupts. Serial communication that appears at the RX
pin is recorded, PWM (see :ref:`pwmWrite() <lang-pwmwrite>`\ ) values
and pin states are maintained, and :ref:`interrupts
<lang-attachinterrupt>` will work as they should.


Example
-------

::

    int ledPin = 13;                 // LED connected to pin 13

    void setup() {
      pinMode(ledPin, OUTPUT);      // sets the digital pin as output
    }

    void loop() {
      digitalWrite(ledPin, HIGH);   // sets the LED on
      delay(1000);                  // waits for a second
      digitalWrite(ledPin, LOW);    // sets the LED off
      delay(1000);                  // waits for a second
    }

.. _lang-delay-seealso:

See Also
--------

- :ref:`millis() <lang-millis>`
- :ref:`micros() <lang-micros>`
- :ref:`delayMicroseconds() <lang-delayMicroseconds>`
- (Arduino) `Blink Without Delay
  <http://arduino.cc/en/Tutorial/BlinkWithoutDelay>`_ example (works
  unmodified on Maple)

.. include:: /arduino-cc-attribution.txt
