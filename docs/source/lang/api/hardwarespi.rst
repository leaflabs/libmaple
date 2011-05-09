.. highlight:: cpp

.. _lang-hardwarespi:

HardwareSPI
===========

This page describes how to use the built-in SPI ports.  It does not
describe the SPI protocol itself.  For more information about SPI, see
the :ref:`SPI reference <spi>`.

.. contents:: Contents
   :local:

Getting Started
---------------

.. TODO [0.1.0] Add a note about calling disableDebugPorts() when
.. using SPI3 on Maple Native

In order to get started, you'll first need to define a ``HardwareSPI``
variable, which you'll use to control the SPI port.  Do this by
putting the line "``HardwareSPI spi(number);``" with your variables,
where ``number`` is the SPI port's number.

Here's an example (we'll fill in :ref:`setup() <lang-setup>` and
:ref:`loop() <lang-loop>` later)::

   // Use SPI port number 1
   HardwareSPI spi(1);

   void setup() {
      // Your setup code
   }

   void loop() {
      // Do stuff with SPI
   }

Turning the SPI Port On
-----------------------

Now it's time to turn your SPI port on.  Do this with the ``begin()``
function (an example is given below).

.. FIXME [0.0.10] Breathe doesn't include the class; fix & submit pull req

.. doxygenfunction:: HardwareSPI::begin

The speed at which the SPI port communicates is configured using a
``SPIFrequency`` value:

.. FIXME [0.1.0] Breathe's enum output is enormous; shrink & submit pull req

.. doxygenenum:: SPIFrequency

.. note:: Due to hardware issues, you can't use the frequency
   ``SPI_140_625KHz`` with SPI port 1.

You'll need to determine the correct values for ``frequency``,
``bitOrder``, and ``mode`` yourself, by consulting the datasheet for
the device you're communicating with.  Continuing our example from
before, we'll add a call to ``begin()`` to our ``setup()``::

   // Use SPI port number 1
   HardwareSPI spi(1);

   void setup() {
       // Turn on the SPI port
       spi.begin(SPI_18MHZ, MSBFIRST, 0);
   }

   void loop() {
      // Do stuff with SPI
   }

If you call ``begin()`` with no arguments (as in "``spi.begin();``"),
it's the same as if you wrote "``spi.begin(SPI_1_125MHZ, MSBFIRST,
0);``".

Communicating Over SPI
----------------------

Now that you've got your SPI port set up, it's time to start
communicating.  You can send data using ``HardwareSPI::write()``,
receive data using ``HardwareSPI::read()``, and do both using
``HardwareSPI::transfer()``.

.. cpp:function:: void HardwareSPI::write(byte data)

   Send a single byte of data.

   **Parameters**:

   - ``data``: Byte to send

.. cpp:function:: byte HardwareSPI::read()

   Get the next available, unread byte.  If there aren't any unread
   bytes, this function will wait until one is received.

.. cpp:function:: byte HardwareSPI::transmit(byte data)

   Send a byte, then return the next byte received.

   **Parameters:**

   - ``data``: Byte to send

   **Returns:** Next unread byte

Continuing our example from before, let's send a number over SPI and
print out whatever we get back over :ref:`lang-serialusb`::

   // Use SPI port number 1
   HardwareSPI spi(1);

   void setup() {
       // Turn on the SPI port
       spi.begin(SPI_18MHZ, MSBFIRST, 0);
   }

   void loop() {
      // Send 245 over SPI, and wait for a response.
      spi.write(245);
      byte response = spi.read();
      // Print out the response received.
      SerialUSB.print("response: ");
      SerialUSB.println(response, DEC);
   }

HardwareSPI Class Reference
---------------------------

There are a number of other things you can accomplish with your
``spi`` object.  A full function listing follows.

.. doxygenclass:: HardwareSPI
   :members: HardwareSPI, begin, beginSlave, end, read, write, transfer

Deprecated Functions
--------------------

The following functions are defined for now, but they have been
deprecated, and will be removed in a future Maple IDE release.  You
shouldn't use them in new programs, and you should change any of your
programs which do use them to the up-to-date functions discussed
above.

.. cpp:function:: uint8 HardwareSPI::send(uint8 *data, uint32 length)

   Writes ``data`` into the port buffer to be transmitted as soon as
   possible, where ``length`` is the number of bytes to send from
   ``data``.  Returns the last byte shifted back from slave.

.. cpp:function:: uint8 HardwareSPI::send(uint8 data)

   Writes the single byte ``data`` into the port buffer to be
   transmitted as soon as possible.  Returns the data byte shifted
   back from the slave.

.. cpp:function:: uint8 HardwareSPI::recv()

   Reads a byte from the peripheral.  Returns the next byte in the
   buffer.
