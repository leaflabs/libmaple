.. _i2c:

=====
|i2c|
=====

.. note::

   The |i2c| interface is currently only available from the 'i2c' branch
   of the github `libmaple <http://github.com/leaflabs/libmaple>`_
   repository.

|i2c| is a crude and easy-to-hack serial protocol that requires only
two wires/channels for communication between many devices.  Every
message passed on the bus is between a *master* (who initiates the
message) and a *slave* device.  Slaves are addressed using 7-bit
addresses (up to 127 unique devices); 10-bit addressing is possible,
but currently unimplemented.  Every message consists of an arbitrary
combination of 8-bit reads and writes as requested by the master.
Higher level functionality, such as reading a particular register
value, is achieved by writing to set the memory location then reading
to pull out the data.

Note that the master/slave designation is on a message-by-message
basis. The Maple can act as both a master (messages initiated by user
code) and slave device (responding to requests via configurable
interrupt handlers) at the same time.

.. contents:: Contents
   :local:

Hardware/Circuit Design
-----------------------

The Maple has two |i2c| ports.  Port 1 (i2c1) has SDA on header D9 and
SCL on D5; Port 2 (i2c2) has SDA on D30 and SCL on D29.

The Maple reliably communicates with up to a 400kHz clock speed; this
doesn't translate into a 400kbps data rate except in extreme cases
because of addressing and protocol overhead. We have tested clock
speeds up to a megahertz and have had mixed results; in theory it
could be possible to achieve even higher rates, but signal quality
degrades rapidly and the bus becomes unreliable.

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

The function API for |i2c| is not finished! See the `source code
<http://github.com/leaflabs/libmaple/blob/i2c/libmaple/i2c.h>`_ for
now.

.. TODO link to libmaple I2C docs once (1) finished, (2) in master

SMBus
-----

The STM32 microcontroller has hardware support for SMBus; we simply
have not written software for it. The SMBAL line for i2c1 is on header
D4 and for i2c2 is on D31.

.. TODO link to libmaple SMBus docs once (1) finished, (2) in master

.. _i2c-recommended-reading:

Recommended Reading
-------------------

* `i2c-bus.org <http://www.i2c-bus.org/>`_
* `Wikipedia Article on i2c <http://en.wikipedia.org/wiki/I%C2%B2C>`_
* `Arduino i2c/TWI reference <http://www.arduino.cc/playground/Learning/I2C>`_
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
  * `Application Note on Advanced I2C Usage
    <http://www.st.com/stonline/products/literature/an/15021.pdf>`_
    (pdf)
