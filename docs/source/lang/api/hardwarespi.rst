.. highlight:: cpp

.. _lang-hardwarespi:

HardwareSPI
===========

This class is used for creating objects to manage the Maple's built-in
SPI ports.  The Maple has two SPI ports.  The relevant pins
corresponding to each port's logic signals are documented in the
following table (and on the Maple silkscreen):

.. _lang-hardwarespi-pinout:

.. list-table::
   :header-rows: 1

   * - Port number
     - NSS
     - MOSI
     - MISO
     - SCK

   * - 1
     - 10
     - 11
     - 12
     - 13

   * - 2
     - 31
     - 32
     - 33
     - 34

If you use a SPI port, you cannot simultaneously use its associated
pins for other purposes.

Library Documentation
---------------------

Using the SPI Class
^^^^^^^^^^^^^^^^^^^

You can declare that you want to use SPI in your sketch by putting
``HardwareSPI Spi(number);`` with your variables, where ``number`` is
1 or 2, depending on which SPI you want to use.  Then you can use the
functions described in the next section.  For example::

   // Use SPI 1
   HardwareSpi Spi(1);

   void setup() {
       Spi.begin(SPI_18MHZ);
   }

   void loop() {
       // Get the next byte from the peripheral
       uint8 byte = Spi.recv();
   }

HardwareSPI Class Reference
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. cpp:class:: HardwareSPI

   Class for interacting with SPI.

.. cpp:function:: HardwareSPI::HardwareSPI(uint32 spi_num)

   Construct an object for managing a SPI peripheral.  ``spi_num``
   must be 1 or 2; see the :ref:`table above
   <lang-hardwarespi-pinout>` for pinout information.

.. cpp:function:: void HardwareSPI::begin(SPIFrequency freq, uint32 endianness, uint32 mode)

   Configure the baudrate of the given SPI port and set up the header
   pins appropriately.

   Parameters:

   - ``freq``: one of the ``SPIFrequency`` values, given :ref:`below
     <lang-hardwarespi-spifrequency>`.

   - ``endianness``: either ``LSBFIRST`` (little-endian) or
     ``MSBFIRST`` (big-endian).

   - ``mode``: one of 0, 1, 2, or 3, and specifies which SPI mode is
     used.  The mode number determines a combination of polarity and
     phase according to the following table:

     .. list-table::
        :header-rows: 1

        * - Mode
          - Polarity
          - Phase

        * - 0
          - 0
          - 0

        * - 1
          - 0
          - 1

        * - 2
          - 1
          - 0

        * - 3
          - 1
          - 1

     For more information on polarity and phase, see the
     :ref:`external references, below <lang-hardwarespi-seealso>`.

.. cpp:function:: void HardwareSPI::begin()

   A convenience ``begin()``, equivalent to ``begin(SPI_1_125MHZ,
   MSBFIRST, 0)``.

.. cpp:function:: uint8 HardwareSpi::send(uint8 *data, uint32 length)

   Writes ``data`` into the port buffer to be transmitted as soon as
   possible, where ``length`` is the number of bytes to send from
   ``data``.  Returns the last byte shifted back from slave.

.. cpp:function:: uint8 HardwareSpi::send(uint8 data)

   Writes the single byte ``data`` into the port buffer to be
   transmitted as soon as possible.  Returns the data byte shifted
   back from the slave.

.. cpp:function:: uint8 HardwareSpi::recv()

   Reads a byte from the peripheral.  Returns the next byte in the
   buffer.

SPI Speeds
^^^^^^^^^^

.. _lang-hardwarespi-spifrequency:

The possible SPI speeds are configured using the ``SPIFrequency`` enum:

.. doxygenenum:: SPIFrequency

.. _lang-hardwarespi-seealso:

See Also
--------

* `Wikipedia Article on Serial Peripheral Interface Bus (SPI)
  <http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus>`_
* `Arduino reference on SPI
  <http://www.arduino.cc/playground/Code/Spi>`_
* `Hardcore SPI on Arduino <http://klk64.com/arduino-spi/>`_ by kik64
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)


