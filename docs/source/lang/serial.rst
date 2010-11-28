.. _lang-serial:

Serial
======

Used for communication between the Arduino board and a computer or
other devices. All Arduino boards have at least one serial port
(also known as a UART or USART): **Serial**. It communicates on
digital pins 0 (RX) and 1 (TX) as well as with the computer via
USB. Thus, if you use these functions, you cannot also use pins 0
and 1 for digital input or output.



You can use the Arduino environment's built-in serial monitor to
communicate with an Arduino board. Click the serial monitor button
in the toolbar and select the same baud rate used in the call to
begin().



The Arduino Mega has three additional serial ports: **Serial1** on
pins 19 (RX) and 18 (TX), **Serial2** on pins 17 (RX) and 16 (TX),
**Serial3** on pins 15 (RX) and 14 (TX). To use these pins to
communicate with your personal computer, you will need an
additional USB-to-serial adaptor, as they are not connected to the
Mega's USB-to-serial adaptor. To use them to communicate with an
external TTL serial device, connect the TX pin to your device's RX
pin, the RX to your device's TX pin, and the ground of your Mega to
your device's ground. (Don't connect these pins directly to an
RS232 serial port; they operate at +/- 12V and can damage your
Arduino board.)



Functions
---------


-  `begin <http://arduino.cc/en/Serial/Begin>`_\ ()
-  `end <http://arduino.cc/en/Serial/End>`_\ ()
-  `available <http://arduino.cc/en/Serial/Available>`_\ ()
-  `read <http://arduino.cc/en/Serial/Read>`_\ ()
-  `flush <http://arduino.cc/en/Serial/Flush>`_\ ()
-  `print <http://arduino.cc/en/Serial/Print>`_\ ()

.. _lang-serial-println:

-  `println <http://arduino.cc/en/Serial/Println>`_\ ()
-  `write <http://arduino.cc/en/Serial/Write>`_\ ()



Examples
--------


-  `ASCII Table <http://arduino.cc/en/Tutorial/ASCIITable>`_
-  `Dimmer <http://arduino.cc/en/Tutorial/Dimmer>`_
-  `Graph <http://arduino.cc/en/Tutorial/Graph>`_
-  `Physical Pixel <http://arduino.cc/en/Tutorial/PhysicalPixel>`_
-  `Virtual Color Mixer <http://arduino.cc/en/Tutorial/VirtualColorMixer>`_
-  `Serial Call Response <http://arduino.cc/en/Tutorial/SerialCallResponse>`_
-  `Serial Call Response ASCII <http://arduino.cc/en/Tutorial/SerialCallResponseASCII>`_



.. include:: cc-attribution.txt
