.. highlight:: cpp

.. _usb:

USB
===

The STM32 microprocessors include a dedicated USB peripheral which can
be configured to act as a general USB slave device with transfer rates
up to 12Mbps. (It unfortunately can't be configured as a host or
on-the-go device).  By default, the peripheral is configured for two
uses: first, to receive sketch/program uploads from the :ref:`IDE
<ide>`, and second, to emulate a regular serial port for use as a
terminal (text read/write).

The emulated terminal is relatively slow and inefficient; it is best
for transferring data at regular serial speeds (kilobaud).  Library
support for accessing the emulated terminal is available at the
:ref:`SerialUSB <lang-serialusb>` reference.

The SerialUSB channel is used with the :ref:`Maple bootloader
<bootloader>` to reprogram the board: a :ref:`magic sequence of
control line toggles and transmitted data <bootloader-rev3>` causes a
Maple to reset itself and enter bootloader mode. As an unfortunate
consequence, the auto-reset will not work if the IDE can not access
the serial port, either due to a conflict with another program (serial
monitor) or because the interface has been disabled from the Maple
side (through :ref:`SerialUSB.end() <lang-serialusb-end>`).  A
solution to the second problem is the use of :ref:`perpetual
bootloader mode <troubleshooting-perpetual-bootloader>`.

Recommended Reading
-------------------

* `USB in a Nutshell <http://www.beyondlogic.org/usbnutshell/usb1.shtml>`_, an overview from Beyond Logic
* `USB made simple <http://www.usbmadesimple.co.uk/>`_, an illustrated series of articles on USB
* The `USB 2.0 Specification <http://www.usb.org/developers/docs/>`_ (`direct link <http://www.usb.org/developers/docs/usb_20_021411.zip>`_)
* `Embedded USB - a brief tutorial <http://www.computer-solutions.co.uk/info/Embedded_tutorials/usb_tutorial.htm>`_
* `Wikipedia article on Universal Serial Bus (USB) <http://en.wikipedia.org/wiki/Universal_Serial_Bus>`_
* Linux Kernel documentation for `USB ACM <http://www.kernel.org/doc/Documentation/usb/acm.txt>`_ and `USB Serial <http://www.kernel.org/doc/Documentation/usb/usb-serial.txt>`_
* ST documentation:
    * Reference Manual `RM0008
      <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
      (PDF), Chapter 23, "Universal serial bus full-speed device
      interface"
    * `Programming Manual
      <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_
      (PDF; assembly language and register reference)
