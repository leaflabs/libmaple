.. _spi:

=====
 SPI
=====

The Maple has two SPI ports. The first has NSS on D10, MOSI on D11,
MISO on D12, and SCK on D13. The second has NSS on D31, SCK on D32,
MISO on D33, and MOSI on D34.

.. _spi-speeds:

Each port can be configured at one of the following speeds:

* ``SPI_18MHZ``: 18 MHz
* ``SPI_9MHZ``: 9 MHz
* ``SPI_4_5MHZ``: 4.5 MHz
* ``SPI_2_25MHZ``: 2.25 MHz
* ``SPI_1_125MHZ``: 1.124 MHz
* ``SPI_562_500KHZ``: 562.500 KHz
* ``SPI_281_250KHZ``: 281.250 KHz
* ``SPI_140_625KHZ``: 140.625 KHz

.. contents:: Contents
   :local:

Function Reference
------------------

``HardwareSPI Spi(number);``

    This declaration must be included at the start of any sketch or
    program that uses the SPI interface. The argument number is either
    1 or 2 and specifies which port to use.

``Spi.begin(freq, endianness, mode)``

    ``begin`` is usually called in `setup()`_ to configure the
    baudrate of the given SPI port and to set up the header pins
    appropriately. ``freq`` is one of the set listed :ref:`above
    <spi-speeds>`; ``endianness`` is either ``LSBFIRST`` or
    ``MSBFIRST``; mode is one of 0, 1, 2, 3, and specifies which "SPI
    Mode" is used (see specification docs linked below).

``Spi.begin()``

    A default ``begin`` with no arguments is provided for the lazy; it
    is equivalent to ``Spi.begin(SPI_1_125MHZ, MSBFIRST, 0)``.

``Spi.send(data, size)``

    Writes data into the port buffer to be transmitted as soon as
    possible.  ``data`` should be an array of type ``byte*``; ``size``
    should be the number of elements in ``data``.

Recommended Reading
-------------------

* `Wikipedia Article on Serial Peripheral Interface Bus (SPI)
  <http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus>`_
* `Arduino reference on SPI
  <http://www.arduino.cc/playground/Code/Spi>`_
* `Hardcore SPI on Arduino <http://klk64.com/arduino-spi/>`_ by kik64
* STMicro documentation for STM32F103RB microcontroller:

  * `All <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
  * `Datasheet (pdf)
    <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_
  * `Reference Manual (pdf)
    <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_

