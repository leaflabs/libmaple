.. _spi:

=====
 SPI
=====

The Serial Peripheral Interface Bus (SPI) is a serial data transfer
protocol useful for interacting with a wide variety of hardware
peripherals.

The Maple has two SPI ports. The first has NSS on D10, MOSI on
D11, MISO on D12, and SCK on D13. The second has NSS on D31, SCK on
D32, MISO on D33, and MOSI on D34.

The public libmaple API for managing the SPI ports is the
:ref:`HardwareSpi <lang-hardwarespi>` class.

Recommended Reading
-------------------

* `Wikipedia Article on Serial Peripheral Interface Bus (SPI)
  <http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus>`_
* `Arduino reference on SPI
  <http://www.arduino.cc/playground/Code/Spi>`_
* `Hardcore SPI on Arduino <http://klk64.com/arduino-spi/>`_ by kik64
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)

