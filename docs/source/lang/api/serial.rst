.. _lang-serial:

Serial Ports (``Serial1``, ``Serial2``, ``Serial3``)
====================================================

Used for communication between the Maple board and a computer or other
devices.

.. contents:: Contents
   :local:

Introduction
------------

.. FIXME [0.0.10] UART4, UART5

To use a serial port to communicate with an external serial device,
connect the TX pin to your device's RX pin, the RX to your device's TX
pin, and your Maple board's ground to your device's ground.

.. warning:: Don't connect these pins directly to an RS232 serial
   port; they operate at +/- 12V and can damage your board.

Library Documentation
---------------------

.. FIXME [0.1.0] Tutorial-style usage introduction

All of the ``Serial[1,2,3]`` objects are instances of the
``HardwareSerial`` class, which is documented in this section.  (This
means that you can use any of these functions on any of ``Serial1``,
``Serial2``, and ``Serial3``).

.. cpp:class:: HardwareSerial

   Serial port class.  Predefined instances are ``Serial1``,
   ``Serial2``, and ``Serial3``.

.. cpp:function:: HardwareSerial::begin(unsigned int baud)

   Set up a ``HardwareSerial`` object for communications.  This method
   must be called before attempting to use the ``HardwareSerial``
   object (typically, you call this in your :ref:`setup()
   <lang-setup>` function).

.. cpp:function:: HardwareSerial::end()

   Disables the USART associated with this object, allowing any
   associated communication pins to be used for other purposes.

.. cpp:function:: unsigned int HardwareSerial::available()

   Returns the number of bytes available for reading.

.. cpp:function:: unsigned char HardwareSerial::read()

   Returns the next available, unread character.  If there are no
   available characters (you can check this with :cpp:func:`available
   <HardwareSerial::available>`), the call will block until one
   becomes available.

.. cpp:function:: HardwareSerial::flush()

   Throw away the contents of the serial port's receiver (RX) buffer.
   That is, clears any buffered characters, so that the next character
   read is guaranteed to be new.

.. cpp:function:: HardwareSerial::print(unsigned char b)

   Print the given byte over the USART.

.. cpp:function:: HardwareSerial::print(char c)

   Print the given character over the USART.  7-bit clean characters
   are typically interpreted as ASCII text.

.. cpp:function:: HardwareSerial::print(const char *str)

   Print the given null-terminated string over the USART.

.. cpp:function:: HardwareSerial::print(int n)

   Print the argument's digits over the USART, in decimal format.
   Negative values will be prefixed with a ``'-'`` character.

.. cpp:function:: HardwareSerial::print(unsigned int n)

   Print the argument's digits over the USART, in decimal format.

.. cpp:function:: HardwareSerial::print(long n)

   Print the argument's digits over the USART, in decimal format.
   Negative values will be prefixed with a ``'-'`` character.

.. cpp:function:: HardwareSerial::print(unsigned long n)

   Print the argument's digits over the USART, in decimal format.

.. cpp:function:: HardwareSerial::print(long n, int base)

   Print the digits of ``n`` over the USART, in base ``base`` (which
   may be between 2 and 16).  The ``base`` value 2 corresponds to
   binary, 8 to octal, 10 to decimal, and 16 to hexadecimal.  Negative
   values will be prefixed with a ``'-'`` character.

.. cpp:function:: HardwareSerial::print(double n)

   Print ``n``, accurate to 2 digits after the decimal point.

.. _lang-serial-println:

.. cpp:function:: HardwareSerial::println(char c)

   Like ``print(c)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(const char *c)

   Like ``print(c)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(unsigned char b)

   Like ``print(b)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(int n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(unsigned int n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(long n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(unsigned long n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(long n, int base)

   Like ``print(n, b)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println(double n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: HardwareSerial::println()

   Prints ``"\r\n"`` over the USART.

.. cpp:function:: HardwareSerial::write(unsigned char ch)

   Sends one character over the USART.  This function is currently
   blocking, although nonblocking writes are a planned future
   extension.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

.. cpp:function:: HardwareSerial::write(const char* str)

   Send the given null-terminated character string over the USART.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

.. cpp:function:: HardwareSerial::write(void *buf, unsigned int size)

   Writes the first ``size`` bytes of ``buf`` over the USART.  Each
   byte is transmitted as an individual character.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

Arduino Compatibility Note
--------------------------

Unlike the Arduino, none of the Maple's serial ports is connected to
the USB port on the Maple board.  If you want to communicate using the
built-in USB port, use :ref:`SerialUSB <lang-serialusb>` instead.  You
will need an additional USB-to-serial adapter to communicate between a
USART and your computer.

.. FIXME [0.1.0] port these examples over

.. Examples
.. --------

.. -  `ASCII Table <http://arduino.cc/en/Tutorial/ASCIITable>`_
.. -  `Dimmer <http://arduino.cc/en/Tutorial/Dimmer>`_
.. -  `Graph <http://arduino.cc/en/Tutorial/Graph>`_
.. -  `Physical Pixel <http://arduino.cc/en/Tutorial/PhysicalPixel>`_
.. -  `Virtual Color Mixer <http://arduino.cc/en/Tutorial/VirtualColorMixer>`_
.. -  `Serial Call Response <http://arduino.cc/en/Tutorial/SerialCallResponse>`_
.. -  `Serial Call Response ASCII <http://arduino.cc/en/Tutorial/SerialCallResponseASCII>`_

.. include:: /arduino-cc-attribution.txt
