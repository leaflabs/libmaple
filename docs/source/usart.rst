.. _usart:

=======
 USART
=======

.. contents::
   :local:

Hardware/Circuit Design
-----------------------

The Maple has 3 separate USART devices: ``Serial1``, ``Serial2``, and
``Serial3``. In the most simple use case, the RX and TX pins are used
to send data at a predetermined baudrate with the line voltage level
relative to ground.

+-----------+--------+-----+
|Port       |Function|Pin  |
+===========+========+=====+
|``Serial1``|TX      |D7   |
|           |        |     |
|           |RX      |D8   |
|           |        |     |
|           |CK      |D6   |
+-----------+--------+-----+
|``Serial2``|TX      |D1   |
|           |        |     |
|           |RX      |D0   |
|           |        |     |
|           |CK      |D10  |
|           |        |     |
|           |CTS     |D2   |
|           |        |     |
|           |RTS     |D3   |
+-----------+--------+-----+
|``Serial3``|TX      |D29  |
|           |        |     |
|           |RX      |D30  |
|           |        |     |
|           |CK      |D31  |
|           |        |     |
|           |CTS     |D32  |
|           |        |     |
|           |RTS     |D33  |
+-----------+--------+-----+

.. TODO make above less ugly

Compatible Devices and Specifications
-------------------------------------

We have successfully used the Maple USART ports with an FT232R-based USB-serial converter at up to 115200 baud; higher speeds should certainly be possible.

Function Reference
------------------

In the following, you may replace ``SerialN`` with ``Serial1``,
``Serial2``, or ``Serial3``.

``SerialN.begin(baudrate)``

    ``SerialN.begin`` is usually called in `setup()`_ to configure the
    baudrate of the given serial port and to set up the header pins
    appropriately. It can be called at any time to reconfigure a port
    or to change the baudrate. 9600 baud is the generic speed most
    widely supported by other devices and terminals.

``SerialN.print(...)``/\ ``SerialN.println(...)``

    Writes data into the port buffer to be transmitted as soon as
    possible. Accepts strings (``char*``). If a raw integer is
    passed, the corresponding ASCII character will be transmitted; to
    print out a number in human readable form add a second parameter
    with the base system. 

    For example, to print out the decimal number '1234' use
    ``SerialN.print(1234, DEC)``; to print out the binary number
    '1001', use ``SerialN.print(9, BIN)``.

``SerialN.available()``/\ ``SerialN.read()``

    ``SerialN.read()`` will return the next unread character that has
    been received over the port. ``SerialN.available()`` returns how
    many such bytes are available (or zero if none are). If none are
    available, ``SerialN.read()`` will block/fail, so the usual
    program structure is to poll with ``SerialN.available`` and only
    read if a nonzero value is returned.

Recommended Reading
-------------------

* `Wikipedia article on Universal asynchronous receiver/transmitter (USART) <http://en.wikipedia.org/wiki/Universal_asynchronous_receiver/transmitter>`_
* `Arduino reference on Serial <http://arduino.cc/en/Reference/Serial>`_
* STMicro documentation for STM32F103RB microcontroller:

  * `All <stm32-all>`_
  * `Datasheet <datasheet>`_ (pdf)
  * `Reference Manual <full-manual>`_ (pdf)
