.. highlight:: cpp

.. _usb:

=====
 USB
=====

.. note:: Changes and Caveats

   The SerialUSB functionality was modified for the 0.0.6 IDE
   release. It now includes a 50 millisecond timeout for writes and
   does not try to detect if the USB host is "really" connected or
   just enumerated and initialized. This means that if you have a
   number of SerialUSB writes or prints in your code and you are not
   monitoring on a computer your program will run much, much slower
   than if it is being monitored or totally disconnected (battery).

   You can avoid this behavior by :ref:`deciphering the port status
   <usb-safe-print>` using the DTR and RTS line status; the behavior
   of these control lines is platform dependent and we no longer
   interpret them by default.

The Maple STM32 microprocessor includes a dedicated USB peripheral
which can be configured to act as a general USB slave device with
transfer rates up to 12Mbps (it unfortunately can't be configured as a
host or on-the-go device).  By default, the peripheral is configured
for two uses: first, to receive sketch/program uploads from the IDE,
and second, to emulate a regular serial port for use as a terminal
(text read/write).

The emulated terminal is relatively slow and inefficient; it is best
for transferring data at regular serial speeds (kilobaud). Users
requiring faster data transfer should consider implementing a
different communications protocol; the Maple could be reprogrammed to
appear as a mass storage device (thumb drive), human interface device
(mouse or keyboard), microphone, or any other USB device.

The SerialUSB channel is also used as part of the auto-reset feature
of the IDE to program the board (on Maple Rev3): a :ref:`magic
sequence of control line toggles and transmitted data
<bootloader-rev3>` causes the Maple to reset itself and enter
bootloader mode. As an unfortunate consequence, the auto-reset will
not work if the IDE can not access the serial port, either due to a
conflict with another program (serial monitor) or because the
interface has been disabled from the Maple side (through
``SerialUSB.end()``).

Function Reference
------------------

``SerialUSB.print(...)``/\ ``SerialUSB.println(...)``

    Writes data into the port buffer to be transmitted as soon as
    possible. Accepts strings (``char*``). If a raw integer is passed
    the corresponding ASCII character will be transmitted; to print
    out a number in human readable form add a second parameter with
    the base system. For example, to print out the decimal number
    "1234", use ``SerialUSB.print(1234, DEC)``; to print out the
    binary number "1001", use ``SerialUSB.print(9, BIN)``.

.. _usb-write:

``SerialUSB.write(bytes)``

    ``write`` is a lower-level function that writes bytes directly
    into the buffer. :ref:`print() <usb-print>` often calls this
    function dozens of times to write out a single formatted number;
    user code can optimize raw data speed by calling this function
    with 64-byte chunks instead.
 
``SerialUSB.available()``/\ ``SerialUSB.read()``

    ``SerialUSB.read()`` will return the next available character
    (``byte``) that has been received over the port.
    ``SerialUSB.available()`` returns how many such bytes are actually
    available. If there is no data, ``read`` will block/fail, so the
    usual program structure is to poll with ``available`` and only
    ``read`` if there are data to read.

``SerialUSB.read(buffer, length)``

    An alternative version of ``SerialUSB.read``; will write the next
    ``length`` available characters into the array ``buffer``.

``SerialUSB.pending()``

    Returns the number of bytes waiting in the transmit
    buffer. Usercode can use this to prevent any blocking/waiting when
    using the direct :ref:`write <usb-write>` functions, or to check
    if data was actually requested/received by the host.

``SerialUSB.getRTS()``

    Returns the state (1 or 0) of the virtual RTS ("ready to send")
    line. This can be used to guess if the USB host is actively
    waiting for data (e.g., if a serial monitor program is running) or
    just "configured" (i.e., the virtual serial port is configured,
    but no program is reading data).

``SerialUSB.getDTR()``

    Returns the state (1 or 0) of the virtual DTR ("data terminal
    ready") line. This can be used to guess if the USB host is
    actively waiting for data (e.g., if a serial monitor program is
    running) or just "configured" (i.e., the virtual serial port is
    configured, but no program is reading data).

.. TODO deprecate crap out of above two functions; write a sane API

``SerialUSB.isConnected()``

    Returns 1 if the USB host is connected and the virtual serial
    interface is initialized (though not necessarily active).
    Otherwise, returns 0.

``SerialUSB.end()``/\ ``SerialUSB.begin()``

    The USB peripheral is enabled by default so that the auto-reset
    feature will work, but it can be disabled/restarted at any time
    with the ``SerialUSB.end()`` and ``SerialUSB.begin()``
    functions.

    ``SerialUSB.end()`` is a relatively hard shutdown, similar to
    unplugging the board; this may crash or confuse any programs
    running host-side.  Note that calling this function will require
    the Maple to be put into :ref:`perpetual bootloader mode
    <troubleshooting-perpetual-bootloader>` before another program can
    be uploaded onto it, unless ``SerialUSB.begin()`` is called before
    the upload is attempted.

    It's probably wise to wait a few seconds between calls to
    ``SerialUSB.end()`` and ``SerialUSB.begin()`` (or to
    ``SerialUSB.begin()`` and ``SerialUSB.print()``) to let the
    computer reconfigure.

Code Examples
-------------

.. _usb-safe-print:

Safe Print
^^^^^^^^^^

This function should run smoothly and not block; the LED should blink
at roughly the same speed whether being monitored, running from
battery, or connected but not monitored. You may need to experiment
with the DTR/RTS logic for your platform and device configuration.  ::

    #define LED_PIN 13

    void setup() {
        /* Set up the LED to blink  */
        pinMode(LED_PIN, OUTPUT);
    }

    void loop() {
        // LED will stay off if we are disconnected;
        // will blink quickly if USB is unplugged (battery etc)
        if(SerialUSB.isConnected()) {
            digitalWrite(LED_PIN, 1);
        }
        delay(100);

        // If this logic fails to detect if bytes are going to
        // be read by the USB host, then the println() will fully
        // many times, causing a very slow LED blink.
        // If the characters are printed and read, the blink will
        // only slow a small amount when "really" connected, and fast 
        // when the virtual port is only configured.
        if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS())) {
            for(int i=0; i<10; i++) {
               SerialUSB.println(123456,BIN); 
            }
        } 
        digitalWrite(LED_PIN, 0);
        delay(100);
    }

Recommended Reading
-------------------

* `USB in a NutShell <http://www.beyondlogic.org/usbnutshell/usb1.htm>`_ overview from Beyond Logic
* `Wikipedia article on Universal Serial Bus (USB) <http://en.wikipedia.org/wiki/Universal_Serial_Bus>`_
* Linux Kernel documentation for `USB ACM <http://www.kernel.org/doc/Documentation/usb/acm.txt>`_ and `USB Serial <http://www.kernel.org/doc/Documentation/usb/usb-serial.txt>`_
* STMicro documentation for STM32F103RB microcontroller:

    * `All documents <stm32-all>`_
    * `Datasheet <datasheet>`_ (pdf)
    * `Reference Manual <full-manual>`_ (pdf)
    * `Programming Manual <stm32-programming>`_ (pdf; assembly
      language and register reference)
