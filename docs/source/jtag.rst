.. highlight:: cpp

.. _jtag:

JTAG
====

.. FIXME [0.1.0] Updated adapter schematic, better information

JTAG is an interface for low-level debugging of digital devices. It
gives instruction by instruction control over the microprocessor and
allows data to be read and written to arbitrary memory and register
locations. It is typically used with a debugging tool like `gdb
<http://www.gnu.org/software/gdb/>`_ when hacking low level routines
and hardware peripherals (we use it when working on :ref:`libmaple
<libmaple>`) or to flash a new bootloader.

Note that the STM32 on the Maple has a built-in low level serial
debugger which could also be used to flash bootloaders, and
:ref:`lang-assert` allows basic debugging over a USART serial channel.
We expect only fairly advanced users to use this feature.

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

The Maple has holes for a 8-pin JTAG header, but that header is not
soldered on.  To use JTAG, simply solder on standard 0.1" pitch male
header pins (either the exact 4 by 2 block, or two 4-pin pieces of
straight breakaway header).

Compatible Devices
------------------

We have had good experience with the `Olimex ARM-USB-OCD
<http://www.olimex.com/dev/arm-usb-ocd.html>`_ device, which costs
about €55 plus shipping (as of April 2011).

Function Reference
------------------

You can disable or enable the JTAG and Serial Wire debugging ports in
software using the ``disableDebugPorts()`` and ``enableDebugPorts()``
functions.

* :ref:`lang-disabledebugports`
* :ref:`lang-enabledebugports`

Recommended Reading
-------------------

* `Wikipedia Article on Joint Test Action Group (JTAG)
  <http://en.wikipedia.org/wiki/Joint_Test_Action_Group>`_

* `STM32, GDB, OpenOCD How To
  <http://fun-tech.se/stm32/OpenOCD/gdb.php>`_

* `LeafLabs Wiki JTAG How To
  <http://wiki.leaflabs.com/index.php?title=Maple_JTAG_How_To>`_

* `LeafLabs forum thread on JTAG
  <http://forums.leaflabs.com/topic.php?id=536>`_

* ST documentation:

  * Reference Manual `RM0008
    <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
    (PDF), Chapter 31, "Debug support", and Chapter 9,
    "General-purpose and alternate function I/Os".
