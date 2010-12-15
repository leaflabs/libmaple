.. _jtag:

======
 JTAG
======

JTAG is an interface for low-level debugging of digital devices. It
gives instruction by instruction control over the microprocessor and
allows data to be read and written to arbitrary memory and register
locations. It is typically used with a debugging tool like `gdb
<http://www.gnu.org/software/gdb/>`_ when hacking low level routines
and hardware peripherals (we use it when working on :ref:`libmaple
<libmaple>`) or to flash a new bootloader.

Note that the STM32 on the Maple has a built-in low level serial
debugger which could also be used to flash bootloaders, and that the
:ref:`ASSERT <language-assert>` framework allows basic debugging over
a USART serial channel.  We expect only fairly advanced users to use
this feature.

.. contents:: Contents
   :local:

Wiring Diagram
--------------

.. figure:: /_static/img/jtag-wiring.png
   :align: center
   :alt: JTAG wiring diagram
   :width: 7.4in

   JTAG wiring diagram (`large version
   <http://leaflabs.com/wp-content/uploads/2010/11/maple-jtagadapter.png>`_)
   to connect a standard 20-pin ARM JTAG device to the 8-pin JTAG port
   on the Maple.

The Maple has holes for a 8-pin JTAG header but that header is not
soldered on by default. If you know ahead of time that you'll be
needing it, and you order `straight from LeafLabs
<http://leaflabs.com/store/>`_, add a comment to your order and we can
probably solder one on for no charge.  Otherwise, you can simply
attach standard 0.1" pitch male header pins (either the exact 4x2
block or two 4-pin pieces of breakaway straight header). For a one-off
usage hack, the header can be jammed in the holes and twisted to
ensure electrical contact.

Compatible Devices
------------------

We have had good experience with the `Olimex ARM-USB-OCD
<http://www.olimex.com/dev/arm-usb-ocd.html>`_ device, which costs
about 55 euro plus shipping (as of November 2010).

Recommended Reading
-------------------

* `Wikipedia Article on Joint Test Action Group (JTAG) <http://en.wikipedia.org/wiki/Joint_Test_Action_Group>`_
* `STM32/gdb/OpenOCD HOWTO <http://fun-tech.se/stm32/OpenOCD/gdb.php>`_
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
* There's a `thread on JTAG
  <http://forums.leaflabs.com/topic.php?id=536>`_ in our `forum`_
  which you may find useful.
