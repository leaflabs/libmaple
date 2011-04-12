.. highlight:: cpp

.. _usb:

=====
 USB
=====

The Maple STM32 microprocessor includes a dedicated USB peripheral
which can be configured to act as a general USB slave device with
transfer rates up to 12Mbps (it unfortunately can't be configured as a
host or on-the-go device).  By default, the peripheral is configured
for two uses: first, to receive sketch/program uploads from the IDE,
and second, to emulate a regular serial port for use as a terminal
(text read/write).

The emulated terminal is relatively slow and inefficient; it is best
for transferring data at regular serial speeds (kilobaud).  Library
support for accessing the emulated terminal is available at the
:ref:`SerialUSB <lang-serialusb>` reference.

The SerialUSB channel is used as part of the auto-reset feature of the
IDE to program the board on Maple Rev 3 and Rev 5: a :ref:`magic
sequence of control line toggles and transmitted data
<bootloader-rev3>` causes the Maple to reset itself and enter
bootloader mode. As an unfortunate consequence, the auto-reset will
not work if the IDE can not access the serial port, either due to a
conflict with another program (serial monitor) or because the
interface has been disabled from the Maple side (through
:ref:`SerialUSB.end() <lang-serialusb-end>`).  A solution to the
second problem is the use of :ref:`perpetual bootloader mode
<troubleshooting-perpetual-bootloader>`.

Recommended Reading
-------------------

* `USB in a Nutshell <http://www.beyondlogic.org/usbnutshell/usb1.htm>`_, an overview from Beyond Logic
* `USB made simple <http://www.usbmadesimple.co.uk/>`_, an illustrated series of articles on USB
* The `USB 2.0 Specification <http://www.usb.org/developers/docs/>`_ (`direct link <http://www.usb.org/developers/docs/usb_20_021411.zip>`_)
* `Embedded USB - a brief tutorial <http://www.computer-solutions.co.uk/info/Embedded_tutorials/usb_tutorial.htm>`_
* `Wikipedia article on Universal Serial Bus (USB) <http://en.wikipedia.org/wiki/Universal_Serial_Bus>`_
* Linux Kernel documentation for `USB ACM <http://www.kernel.org/doc/Documentation/usb/acm.txt>`_ and `USB Serial <http://www.kernel.org/doc/Documentation/usb/usb-serial.txt>`_
* STMicro documentation for STM32F103RB microcontroller:

    * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
    * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
    * `Programming Manual <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_ (pdf; assembly
      language and register reference)
