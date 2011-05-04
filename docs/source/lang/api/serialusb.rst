.. highlight:: cpp

.. _lang-serialusb:

``SerialUSB``
=============

Used for communication between the Maple board and a computer.

.. contents:: Contents
   :local:

Introduction
------------

In addition to three :ref:`serial ports <lang-serial>`, the Maple's
STM32 microprocessor includes a dedicated USB peripheral.  This
peripheral is used to emulate a regular serial port for use as a
terminal.  The emulated terminal is relatively slow; it is best for
transferring data at regular serial speeds (kilobaud).

Library access to the emulated serial port is provided through the
``SerialUSB`` object.  You can mostly use ``SerialUSB`` as a drop-in
replacement for ``Serial1``, ``Serial2``, and ``Serial3``.

.. warning:: The ``SerialUSB`` functionality includes a 50 millisecond
   timeout for writes, and does not try to detect if the USB host is
   "really" connected, or just enumerated and initialized.

   This means that if you have a number of calls to one of the
   ``SerialUSB`` ``write()`` or ``print()`` functions in your code,
   and you are not monitoring ``SerialUSB`` on a computer, your
   program will run much slower than if it is being monitored or
   totally disconnected (run off of a battery).

   You can avoid this behavior by :ref:`deciphering the port status
   using the DTR and RTS line status <lang-serialusb-safe-print>` (the
   behavior of these control lines is platform dependent and we no
   longer interpret them by default).

Library Documentation
---------------------

The ``SerialUSB`` object is an instance of the ``USBSerial`` class,
which is documented in this section.  This means that you can use any
of these functions by writing
``SerialUSB.functionName(arguments...)``.  For example, to print the
message "hello, world!", you can write ``USBSerial.println("hello,
world!")``.

.. cpp:class:: USBSerial

   Emulated serial-over-USB class.  ``SerialUSB`` is the predefined
   (singleton) instance.

.. _lang-serialusb-begin:

.. cpp:function:: USBSerial::begin()

   Set up the USB peripheral for emulated serial communication.  The
   peripheral is configured this way by default; calling this function
   should only be necessary if you have disabled the peripheral using
   ``SerialUSB.end()``.

.. _lang-serialusb-end:

.. cpp:function:: USBSerial::end()

   Disables the USB peripheral.  Note that using this function will
   terminate all USB communications between the Maple and the USB
   host; in particular, it implies that you won't be able to upload
   any new programs without resetting the board or using
   :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>`.

.. cpp:function:: unsigned int USBSerial::available()

   Returns the number of bytes available for reading.

.. _lang-serialusb-read:

.. cpp:function:: unsigned char USBSerial::read()

   Returns the next available, unread character.  If there are no
   available characters (you can check this with :cpp:func:`available
   <USBSerial::available>`), the call will block until one
   becomes available.

.. cpp:function:: USBSerial::print(unsigned char b)

   Print the given byte over the USB connection.

.. cpp:function:: USBSerial::print(char c)

   Print the given character over the USB connection.  7-bit clean characters
   are typically interpreted as ASCII text.

.. cpp:function:: USBSerial::print(const char *str)

   Print the given null-terminated string over the USB connection.

.. cpp:function:: USBSerial::print(int n)

   Print the argument's digits over the USB connection, in decimal format.
   Negative values will be prefixed with a ``'-'`` character.

.. cpp:function:: USBSerial::print(unsigned int n)

   Print the argument's digits over the USB connection, in decimal format.

.. cpp:function:: USBSerial::print(long n)

   Print the argument's digits over the USB connection, in decimal
   format.  Negative values will be prefixed with a ``'-'`` character.

.. cpp:function:: USBSerial::print(unsigned long n)

   Print the argument's digits over the USB connection, in decimal
   format.

.. cpp:function:: USBSerial::print(long n, int base)

   Print the digits of ``n`` over the USB connection, in base ``base``
   (which may be between 2 and 16).  The ``base`` value 2 corresponds
   to binary, 8 to octal, 10 to decimal, and 16 to hexadecimal.
   Negative values will be prefixed with a ``'-'`` character.

.. cpp:function:: USBSerial::print(double n)

   Print ``n``, accurate to 2 digits after the decimal point.

.. _lang-serialusb-println:

.. cpp:function:: USBSerial::println(char c)

   Like ``print(c)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(const char *c)

   Like ``print(c)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(unsigned char b)

   Like ``print(b)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(int n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(unsigned int n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(long n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(unsigned long n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(long n, int base)

   Like ``print(n, b)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println(double n)

   Like ``print(n)``, followed by ``"\r\n"``.

.. cpp:function:: USBSerial::println()

   Prints ``"\r\n"`` over the USB connection.

.. cpp:function:: USBSerial::write(unsigned char ch)

   Sends one character over the USB connection.  This function is
   currently blocking, although nonblocking writes are a planned
   future extension.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

.. cpp:function:: USBSerial::write(const char* str)

   Send the given null-terminated character string over the USB
   connection.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

.. cpp:function:: USBSerial::write(void *buf, unsigned int size)

   Writes the first ``size`` bytes of ``buf`` over the USB connection.
   Each byte is transmitted as an individual character.

   This is a low-level function.  One of the ``print()`` or
   ``println()`` functions is likely to be more useful when printing
   multiple characters, when formatting numbers for printing, etc.

Examples
--------

.. _lang-serialusb-safe-print:

**Safe print**: This function should run smoothly and not block; the
LED should blink at roughly the same speed whether being monitored,
running from battery, or connected but not monitored. You may need to
experiment with the DTR/RTS logic for your platform and device
configuration. ::

    #define LED_PIN BOARD_LED_PIN

    void setup() {
        /* Set up the LED to blink  */
        pinMode(LED_PIN, OUTPUT);
    }

    void loop() {
        // LED will stay off if we are disconnected, and will blink
        // quickly if USB is unplugged (battery power, etc.).
        if(SerialUSB.isConnected()) {
            digitalWrite(LED_PIN, 1);
        }
        delay(100);

        // If this logic fails to detect if bytes are going to be read
        // by the USB host, then the println() take a long time,
        // causing a very slow LED blink.  If the characters are
        // printed and read, the blink will only slow a small amount
        // when "really" connected, and will be fast fast when the
        // virtual port is only configured.
        if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS())) {
            for(int i = 0; i < 10; i++) {
               SerialUSB.println(123456, BIN);
            }
        }
        digitalWrite(LED_PIN, 0);
        delay(100);
    }

