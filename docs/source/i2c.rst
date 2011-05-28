.. _i2c:

|i2c|
=====

|i2c| is a crude and easy-to-hack serial protocol that requires only
two wires/channels for communication between Maple and many other
devices.

.. contents:: Contents
   :local:

Overview
--------

Communication via |i2c| is broken up into messages.  Every message is
between a *master* device, which initiates the message, and a *slave*
device, which responds.

Slaves are addressed using 7-bit addresses (up to 127 unique devices);
10-bit addressing is also possible.  Every message consists of an
arbitrary combination of 8-bit reads and writes as requested by the
master.  Higher level functionality, such as reading a particular
register value, is achieved by writing to set the memory location then
reading to pull out the data.

Note that the master/slave designation is on a message-by-message
basis. Maple can act as both a master (messages initiated by user
code) and slave device (responding to requests via configurable
interrupt handlers) at the same time (though slave mode is currently
unimplemented).

Hardware/Circuit Design
-----------------------

.. FIXME [0.1.0] Link to board-specific values (BOARD_I2C1_SDA_PIN, etc.)

Maple boards have two |i2c| ports.  Maples reliably communicate with
up to a 400kHz clock speed; this doesn't translate into a 400kbps
data rate except in extreme cases because of addressing and protocol
overhead.  We have tested clock speeds up to a megahertz and have had
mixed results; in theory, it could be possible to achieve even higher
rates, but signal quality degrades rapidly, and the bus becomes
unreliable.

Proper wiring and pull-up resistor selection are essential when
incorporating |i2c| into a circuit, especially with data rates above
100kHz. In the lab, we usually use approximately 5kΩ resistors with
|vcc| (3.3V) as the high voltage, and try to connect the pullup
voltage as close to the SDA and SCL pins as possible.  We recommend
looking at the ST reference website for |i2c| (see the
:ref:`recommended reading <i2c-recommended-reading>` below), starting
with a slow clock rate (10kHz), and, if possible, using an
oscilloscope to debug any issues.

Function Reference
------------------

Currently, only low-level support in :ref:`libmaple-i2c` exists.  A
Wiring-style library is planned for a future release.

SMBus
-----

The STM32 microcontroller has hardware support for SMBus, but software
for it is not yet implemented.

.. _i2c-recommended-reading:

Recommended Reading
-------------------

* `I2C Bus <http://www.i2c-bus.org/>`_
* `Wikipedia: I2C <http://en.wikipedia.org/wiki/I%C2%B2C>`_
* `Arduino I2C/TWI reference <http://www.arduino.cc/playground/Learning/I2C>`_
* ST `Application Note on Advanced I2C Usage
  <http://www.st.com/stonline/products/literature/an/15021.pdf>`_ (PDF)
