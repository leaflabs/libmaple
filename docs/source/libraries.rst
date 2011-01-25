.. highlight:: c++
.. default-domain:: cpp

.. _libraries:

=========================
 Maple Library Reference
=========================

.. Note: if you port an Arduino library and document it here, be sure
.. to update compatibility.rst to reflect that fact.

This page briefly summarizes the Arduino libraries that have been
ported to Maple. You can use a library from within a sketch by going
to Sketch > Import Library... from within the IDE, then choosing the
library you want.

Any incompatibilities between the Maple and Arduino versions are noted
in the description of the library.

.. contents:: Contents
   :local:

.. toctree::
   :hidden:

   libs/servo.rst

.. _libraries-servo:

Servo
-----

The Servo library is provided for convenient control of RC
servomotors.  For more information, see the :ref:`Servo <libs-servo>`
reference.

**Compatibility Note**

The Servo class provides a public interface identical to the Arduino
version's documented functionality (as of Arduino 0021), so in most
cases, this library will be a drop-in replacement.

However, there are some differences, essentially at the level of
implementation details.

The major difference is that while the Arduino implementation drives
the servos with "bit-banged" :ref:`PWM <pwm>`, the Maple
implementation uses :ref:`timers <timers>` to drive the PWM directly.

Consequently, **the Maple implementation only allows Servo instances
to** :ref:`attach <libs-servo-attach>` **to pins that support PWM**.

To determine if a pin supports PWM (15 Maple pins do), you can either
check if "PWM" appears next to its number on the Maple silkscreen, or
consult the :ref:`pwmWrite() <lang-pwmwrite>` documentation.

RC Servos expect a pulse approximately every 20ms.  In the Maple
implementation, :ref:`periods <lang-hardwaretimer-setperiod>` are set
for entire timers, rather than individual channels.  Thus,
``attach()``\ ing a Servo to a pin can interfere with other pins
associated with the same timer\ [#fard-servo]_.

Because of this, we recommend connecting multiple servomotors to pins
which share a timer, in order to keep as many timers free for other
purposes as possible.  Consult the :ref:`table provided in the timers
reference <timers-pin-channel-map>` to match up pins and timer
channels.

Another difference: although it is not publicly documented to do so,
the Arduino implementation of `attach()
<http://arduino.cc/en/Reference/ServoAttach>`_ returns the timer
channel associated with the newly-attached pin, or 0 on failure (as of
Arduino 0021).  The Maple implementation returns true on success, and
false on failure (and this is its documented behavior).

.. _libraries-liquid-crystal:

LiquidCrystal
-------------

.. TODO 0.0.10 make our own LiquidCrystal docs

The LiquidCrystal library allows Maple to control LCD screens. For
more information, see the `Arduino LiquidCrystal documentation
<http://www.arduino.cc/en/Reference/LiquidCrystal>`_.

**Compatibility Note**

At this time, no incompatibilities between the Maple and Arduino
versions are known. Any observed differences should be considered
bugs, and reported on the forums.

.. _libraries-wire:

Wire
----

We provide a soft (bit-banged) implementation of the `Wire I2C library
<http://arduino.cc/en/Reference/WireBegin>`_.

**Compatibility Note**

This implementation is synchronous, and thus supports only a subset of
the full Wire interface (however, the functionality which is supported
is fully compatible with Arduino). For now, please use the function
reference which follows when developing projects using our
implementation.

Please note that the current implementation only supports master mode
using a bit-banged (software) protocol. Future enhancements will use
the hardware i2c peripheral on the stm32 as well as the DMA for
performance. Support for slave, smBUS, and multimaster modes are also
slated for inclusion in the enhanced Wire port.

.. TODO 0.0.10 Wire docs in the cpp domain in own page under /libs/

Wire Function Reference
^^^^^^^^^^^^^^^^^^^^^^^

``Wire.begin()``
    Joins the i2c bus as master, using pin 20 as SDA and pin 21 as SCL
    (this is compatible with the pin settings on the Arduino Mega).

``Wire.begin(sda, scl)``
    Like ``Wire.begin()``, but with the given pins as SDA and
    SCL.

``Wire.beginTransmission(slave_address)``
    Set up a transmission to a slave device with the given (7-bit)
    address. Bytes subsequently queued for transmission (using
    ``Wire.send``) will be sent to ``slave_address`` when ``void
    Wire.endTransmission()`` is called.

``void Wire.send(byte)``
    Queues the given byte (``uint8`` or ``int``) to the slave address
    previously specified by a call to ``Wire.beginTransmission``. At
    most 32 bytes may be queued in a single transmission.

``Wire.send(string)``
    Queues a given string (``char*``) for transmission. The characters
    of the string are individually queued for transmission as
    bytes. At most 32 bytes may be queued in a single transmission.

``Wire.send(buffer, length)``
    Queues a byte buffer ``buffer`` (``uint8*`` or ``int*``), with
    ``length`` elements, for transmission. At most 32 bytes may be
    queued in a single transmission.

``Wire.endTransmission()``
    Ends a transmission (begun by ``Wire.beginTransmission(uint8)``),
    and actually sends the bytes queued by calls to Wire.send.

    The return value is one of the following status codes:

    * ``SUCCESS``: All bytes were transmitted successfully.

    * ``EDATA``: More than 32 bytes were queued for transmission. No
      bytes are actually sent when this happens.

    * ``ENACKADDR``: Did not receive ACK on transmit of address. No
      bytes are actually sent when this happens.

    * ``ENACKTRNS``: Did not receive ACK during transmit of data. Some
      bytes may have been sent when this happens; however, the
      transmission is aborted after the first byte of data which is
      not ACKed by the slave device.

    * ``EOTHER``: Other error occurred.

``Wire.requestFrom(address, num_bytes)``
    Requests ``num_bytes`` bytes from 7-bit slave address
    address. Returns the actual number of bytes read. These bytes may
    subsequently be read one at a time using ``Wire.receive()``.

    Note: if ``num_bytes`` exceeds the size of the transmit/receive
    buffer (currently 32), it will be truncated to 32.

``Wire.receive()``
    Get and return the next byte read during the previous call to
    ``Wire.requestFrom(uint8, int)``. You can check how many bytes are
    left to read using ``uint8 Wire.available()``.

``Wire.available()``
    Returns the number of bytes which are still available for reading
    (with ``Wire.receive()``) from the last call to
    ``Wire.requestFrom(uint8, int)``.

.. rubric:: Footnotes

.. [#fard-servo] The Arduino implementation also captures timer
   channels in groups as more Servo objects are attached, but the
   details of which channels have their periods reset when are
   slightly different.
