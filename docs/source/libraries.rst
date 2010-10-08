.. highlight:: c++
.. default-domain:: cpp

.. _libraries:

=========================
 Maple Library Reference
=========================

This page briefly summarizes the Arduino libraries that have been ported to Maple. You can use a library from within a sketch by going to Sketch > Import Library... from within the IDE, then choosing the library you want.

Any incompatibilities between the Maple and Arduino versions are noted in the description of the library.

* :ref:`LiquidCrystal <liquid_crystal>`
* :ref:`Wire <wire>`

.. _liquid_crystal:

LiquidCrystal
-------------

The LiquidCrystal library allows Maple to control LCD screens. For more information, see the Arduino LiquidCrystal documentation.
Compatibility Note

At this time, no incompatibilities between the Maple and Arduino versions are known. Any observed differences should be considered bugs, and reported on the forums.

.. _wire:

Wire
----

We provide a soft (bit-banged) implementation of the `Wire I2C library
<http://arduino.cc/en/Reference/WireBegin>`_.

Compatibility Note
^^^^^^^^^^^^^^^^^^

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

Function Reference
^^^^^^^^^^^^^^^^^^

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
