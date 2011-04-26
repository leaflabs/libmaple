.. _usart:

=======
 USART
=======

.. contents:: Contents
   :local:

Hardware/Circuit Design
-----------------------

.. FIXME [0.0.10] UART4 and UART5
.. FIXME [0.1.0] Maple Native and Mini info and links

The Maple has 3 separate USART devices. In the most simple use case,
the RX and TX pins are used to send data at a predetermined baudrate
with the line voltage level relative to ground.  Their usage is
documented in the :ref:`Serial Ports <lang-serial>` language reference
page.  Which pins correspond to the USART TX and RX pins are given on
your board's silkscreen, and also in the board-specific USART pin maps
available here:

* :ref:`Maple <maple-usart-map>`
* :ref:`Maple RET6 Edition <maple-ret6-usart-map>`

If you use a particular serial port, you cannot also use its
communication pins for other purposes at the same time.

Compatible Devices and Specifications
-------------------------------------

We have successfully used the USART ports with an FT232R-based
USB-serial converter at up to 115200 baud.  Higher speeds should
certainly be possible.

Recommended Reading
-------------------

* `Wikipedia article on Universal asynchronous receiver/transmitter (USART) <http://en.wikipedia.org/wiki/Universal_asynchronous_receiver/transmitter>`_
* `Arduino reference on Serial <http://arduino.cc/en/Reference/Serial>`_
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
