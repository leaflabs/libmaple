.. _usart:

USART
=====

.. contents:: Contents
   :local:

Hardware/Circuit Design
-----------------------

.. FIXME [0.0.12/Maple Native] UART4 and UART5, Native links
.. FIXME [0.0.11] Mini info and links

Each LeafLabs board has at least 3 separate USART devices. In the most
simple use case, the RX and TX pins are used to send data at a
predetermined baud rate with the line voltage level relative to
ground.  Their usage is documented in the :ref:`Serial Ports
<lang-serial>` language reference page.

Which pins correspond to the USART TX and RX pins are given on your
board's silkscreen, and also in the board-specific USART pin maps
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

* `Wikipedia article on Universal Asynchronous Receiver/Transmitter
  (USART)
  <http://en.wikipedia.org/wiki/Universal_asynchronous_receiver/transmitter>`_
* `Arduino Serial reference
  <http://arduino.cc/en/Reference/Serial>`_
* ST `Reference Manual RM0008
  <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
  (PDF), Chapter 27.
