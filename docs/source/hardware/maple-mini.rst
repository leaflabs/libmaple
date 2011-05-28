.. _maple-mini:

Maple Mini
==========

This page is a general resource for information specific to the Maple
Mini.  The Maple Mini is a smaller version of the Maple that fits on a
breadboard.

.. contents:: Contents
   :local:

.. TODO [dma.rst] Ref to dma.rst in sequel instead of libmaple-dma

Technical Specifications
------------------------

* MCU: **STM32F103RCBT6**, a 32-bit ARM Cortex M3 microprocessor
* Clock Speed: **72 MHz**
* **128 KB Flash** and **20 KB SRAM**
* 34 Digital I/O Pins (:ref:`gpio`)
* 12 **PWM** pins at 16 bit resolution (:ref:`pwm`)
* 9 analog input pins, 12 bit **ADC** resolution (:ref:`adc`)
* 2 **SPI** peripherals (:ref:`spi`)
* 2 **I2C** peripherals (:ref:`i2c`)
* 7 Channels of Direct Memory Access (**DMA**) (:ref:`libmaple-dma`)
* 3 **USART** peripherals (:ref:`usart`)
* 1 advanced and 3 general-purpose **timers** (:ref:`timers`)
* Dedicated **USB** port for programming and communications (:ref:`usb`)
* **JTAG** (:ref:`jtag`)
* Nested Vectored Interrupt Controller (NVIC) (including
  :ref:`external interrupt <external-interrupts>` on GPIOs)
* Supplies up to 500 mA at 3.3 V, with :ref:`separate 250 mA digital
  and analog regulators <maple-mini-adc-bank>` for low-noise analog
  performance
* :ref:`Four layer design <maple-mini-hardware>`
* Support for low power, sleep, and standby modes (<500 μA)
* Operating Voltage: 3.3 V
* Input Voltage (recommended): 3 V — 12 V
* Dimensions: 2.02″ × 0.72″

.. _maple-mini-powering:

Powering the Maple Mini
-----------------------

You can power the Maple Mini via the USB plug or by powering Vin
directly.

.. warning:: The silkscreen on the Maple Mini suggests it will accept
   an input voltage up to 16 V.  We recommend applying **no greater
   than 12 V**.

   See :ref:`this erratum <maple-mini-vin>` for more information.

.. _maple-mini-gpios:

GPIO Information
----------------

The Maple Mini features 34 total input/output pins, numbered ``D0``
through ``D33``.  These numbers correspond to the numeric values next
to each header on the Maple Mini's silkscreen.  However, some of them
have special uses by default [#fusedpins]_.

.. _maple-mini-usb-pins:

Pin ``D23`` is the :ref:`USB <usb>` D+ line, and ``D24`` is the USB D-
line.  To use them as GPIOs, your program will need to :ref:`disable
SerialUSB <lang-serialusb-end>` first.  Be aware, however, that
disabling SerialUSB means that the :ref:`bootloader <bootloader>`
won't work properly, and you'll need to use
:ref:`troubleshooting-perpetual-bootloader` to make your next upload.

.. _maple-mini-but:

Pin ``D32`` is the Mini's :ref:`button pin <lang-board-values-but>`.
It is thus mainly useful as an :ref:`input <lang-pin-levels>`.  The
pin will :ref:`read <lang-digitalread>` ``HIGH`` when the :ref:`button
is pressed <lang-isbuttonpressed>`.

.. _maple-mini-led:

Pin ``D33`` is the Mini's :ref:`LED pin <lang-board-values-led>`.  It
is thus mainly useful as an :ref:`output <lang-pin-levels>`.  The LED
will glow when ``HIGH`` is :ref:`written <lang-digitalwrite>` to it.
(It also supports :ref:`pwm`, for finer-grained brightness control).

.. TODO [0.1.0] silkscreen pictures which expand abbreviations

.. _maple-mini-pin-map-master:

Master Pin Map
^^^^^^^^^^^^^^

This table shows a summary the available functionality on every GPIO
pin, by peripheral type.  The "5 V?" column documents whether or not
the pin is :ref:`5 volt tolerant <gpio-5v-tolerant>`.

.. csv-table::
   :header: Pin, :ref:`GPIO <gpio>`, :ref:`ADC <adc>`, :ref:`Timer <timers>`, :ref:`I2C <i2c>`, :ref:`UART <usart>`, :ref:`SPI <spi>`, 5 V?

   D0,  PB11,   -, -,         2_SDA,  3_RX,  -,      Yes
   D1,  PB10,   -, -,         2_SCL,  3_TX,  -,      Yes
   D2,  PB2,    -, -,         -,      -,     -,      Yes
   D3,  PB0,  CH8, 3_CH3,     -,      -,     -,      -
   D4,  PA7,  CH7, 3_CH2,     -,      -,     1_MOSI, -
   D5,  PA6,  CH6, 3_CH1,     -,      -,     1_MISO, -
   D6,  PA5,  CH5, -,         -,      -,     1_SCK,  -
   D7,  PA4,  CH4, -,         -,      2_CK,  1_NSS,  -
   D8,  PA3,  CH3, 2_CH4,     -,      2_RX,  -,      -
   D9,  PA2,  CH2, 2_CH3,     -,      2_TX,  -,      -
   D10, PA1,  CH1, 2_CH2,     -,      2_RTS, -,      -
   D11, PA0,  CH0, 2_CH1_ETR, -,      2_CTS, -,      -
   D12, PC15,   -, -,         -,      -,     -,      -
   D13, PC14,   -, -,         -,      -,     -,      -
   D14, PC13,   -, -,         -,      -,     -,      -
   D15, PB7,    -, 4_CH2,     1_SDA,  -,     -,      Yes
   D16, PB6,    -, 4_CH1,     2_SCL,  -,     -,      Yes
   D17, PB5,    -, -,         1_SMBA, -,     -,      -
   D18, PB4,    -, -,         -,      -,     -,      Yes
   D19, PB3,    -, -,         -,      -,     -,      Yes
   D20, PA15,   -, -,         -,      -,     -,      Yes
   D21, PA14,   -, -,         -,      -,     -,      Yes
   D22, PA13,   -, -,         -,      -,     -,      Yes
   D23, PA12,   -, 1_ETR,     -,      1_RTS, -,      Yes
   D24, PA11,   -, 1_CH4,     -,      1_CTS, -,      Yes
   D25, PA10,   -, 1_CH3,     -,      1_RX,  -,      Yes
   D26, PA9,    -, 1_CH2,     -,      1_TX,  -,      Yes
   D27, PA8,    -, 1_CH1,     -,      1_CK,  -,      Yes
   D28, PB15,   -, -,         -,      -,     2_MOSI, Yes
   D29, PB14,   -, -,         -,      3_RTS, 2_MISO, Yes
   D30, PB13,   -, -,         -,      3_CTS, 2_SCK,  Yes
   D31, PB12,   -, 1_BKIN,    2_SMBA, 3_CK,  2_NSS,  Yes
   D32, PB8,    -, 4_CH3,     -,      -,     -,      Yes
   D33, PB1,  CH9, 3_CH4,     -,      -,     -,      -

.. _maple-mini-timer-map:

Timer Pin Map
^^^^^^^^^^^^^

The following table shows what pins are associated with a particular
timer's capture/compare channels.

.. csv-table::
   :header: Timer, Ch. 1, Ch. 2, Ch. 3, Ch. 4
   :delim: |

   1 | D27 | D26 | D25                         | D24
   2 | D11 | D10 | D9                          | D8
   3 | D5  | D4  | D3                          | :ref:`D33 <maple-mini-led>`
   4 | D16 | D15 | :ref:`D32 <maple-mini-but>` |

.. _maple-mini-exti-map:

EXTI Line Pin Map
^^^^^^^^^^^^^^^^^

The following table shows which pins connect to which :ref:`EXTI lines
<external-interrupts-exti-line>` on the Maple.

.. list-table::
   :widths: 1 1
   :header-rows: 1

   * - EXTI Line
     - Pins
   * - EXTI0
     - 3, 11
   * - EXTI1
     - 10, 33
   * - EXTI2
     - 2, 9
   * - EXTI3
     - 8, 19
   * - EXTI4
     - 7, 18
   * - EXTI5
     - 6, 17
   * - EXTI6
     - 5, 16
   * - EXTI7
     - 4, 15
   * - EXTI8
     - 27, 32
   * - EXTI9
     - 26
   * - EXTI10
     - 1, 25
   * - EXTI11
     - 0, 24
   * - EXTI12
     - 23, 31
   * - EXTI13
     - 14, 22, 30
   * - EXTI14
     - 13, 21, 29
   * - EXTI15
     - 12, 20, 28

.. _maple-mini-usart-map:

USART Pin Map
^^^^^^^^^^^^^

The Maple RET6 Edition has three serial ports whose pins are broken
out to headers (also known as :ref:`USARTs <usart>`). They communicate
using the pins summarized in the following table:

.. csv-table::
   :header: Serial Port, TX, RX, CK, CTS, RTS
   :delim: |

   ``Serial1`` | 26 | 25 | 27 | 24 | 23
   ``Serial2`` | 9  |  8 |  7 | 11 | 10
   ``Serial3`` | 1  |  0 | 31 | 30 | 29

.. _maple-mini-adc-bank:

Low-Noise ADC Pins
^^^^^^^^^^^^^^^^^^

Maple Mini has an electrically isolated analog power plane with its
own regulator, and a geometrically isolated ground plane, connected to
the digital plane by an inductor.  Its analog input pins, D3 — D11,
are laid out to correspond with these analog planes, and our
measurements indicate that they generally offer low noise ADC
performance.  However, analog performance may vary depending upon the
activity of the other GPIOs.  Consult the :ref:`Maple Mini hardware
design files <maple-mini-hardware>` for more details.

.. _maple-mini-board-values:

Board-Specific Values
---------------------

This section lists the Maple Mini's :ref:`board-specific values
<lang-board-values>`.

- ``CYCLES_PER_MICROSECOND``: 72
- ``BOARD_BUTTON_PIN``: 32
- ``BOARD_LED_PIN``: 33
- ``BOARD_NR_GPIO_PINS``: 34
- ``BOARD_NR_PWM_PINS``: 12
- ``boardPWMPins``: 3, 4, 5, 8, 9, 10, 11, 15, 16, 25, 26, 27
- ``BOARD_NR_ADC_PINS``: 9
- ``boardADCPins``: 3, 4, 5, 6, 7, 8, 9, 10, 11
- ``BOARD_NR_USED_PINS``: 4
- ``boardUsedPins``: ``BOARD_LED_PIN``, ``BOARD_BUTTON_PIN``, 23, 24
  (23 and 24 are used by :ref:`USB <maple-mini-usb-pins>`)
- ``BOARD_NR_USARTS``: 3
- ``BOARD_USART1_TX_PIN``: 26
- ``BOARD_USART1_RX_PIN``: 25
- ``BOARD_USART2_TX_PIN``: 9
- ``BOARD_USART2_RX_PIN``: 8
- ``BOARD_USART3_TX_PIN``: 1
- ``BOARD_USART3_RX_PIN``: 0
- ``BOARD_NR_SPI``: 2
- ``BOARD_SPI1_NSS_PIN``: 7
- ``BOARD_SPI1_MOSI_PIN``: 4
- ``BOARD_SPI1_MISO_PIN``: 5
- ``BOARD_SPI1_SCK_PIN``: 6
- ``BOARD_SPI2_NSS_PIN``: 31
- ``BOARD_SPI2_MOSI_PIN``: 28
- ``BOARD_SPI2_MISO_PIN``: 29
- ``BOARD_SPI2_SCK_PIN``: 30
- ``BOARD_JTMS_SWDIO_PIN``: 22
- ``BOARD_JTCK_SWCLK_PIN``: 21
- ``BOARD_JTDI_PIN``: 20
- ``BOARD_JTDO_PIN``: 19
- ``BOARD_NJTRST_PIN``: 18

.. _maple-mini-hardware:

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple Mini GitHub repository <https://github.com/leaflabs/maplemini>`_

From the GitHub repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `Git <http://git-scm.com/>`_, you can also clone the repository
at the command line with ::

    $ git clone git://github.com/leaflabs/maplemini.git

Failure Modes
-------------

The following known failure modes apply to all Maple boards.  The
failure modes aren't design errors, but are easy ways to break or
damage your board permanently.

* **High voltage on non-tolerant pins**: not all header pins are 5 V
  compatible; so e.g. connecting certain serial devices in the wrong
  way could over-voltage the pins.  The :ref:`pin-mapping master table
  <maple-mini-pin-map-master>` details which pins are :ref:`5
  V-tolerant <gpio-5v-tolerant>`.

Errata
------

This section lists known issues and warnings for the Maple Mini Rev 2
(the first Rev sold to the public).

.. _maple-mini-vin:

* **Silkscreen Vin voltage mistake**: The silkscreen on the Maple Mini
  falsely indicates that Vin may be supplied with up to 16 V.  We
  recommend an input voltage **no greater than 12 V**.

  The voltage regulator on the Mini is rated up to 16 V.  However, our
  tests indicate that as its input voltage approaches 16 V, its output
  begins to rise to levels higher than those recommended by ST for
  supplying the STM32F103CB.  The limit of 12 V keeps the voltage
  supplied to the processor at safe levels.

Recommended Reading
-------------------

STMicro documentation for STM32F103CB microcontroller:

* `Datasheet
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00161566.pdf>`_
  (PDF); covers STM32F103x8, STM32F103xB.
* `Reference Manual RM0008
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf>`_
  (PDF); general, definitive resource for STM32F1 line.
* `Programming Manual PM0056
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/PROGRAMMING_MANUAL/CD00228163.pdf>`_
  (PDF); assembly language and register reference.
* `STM32F103CB <http://www.st.com/internet/mcu/product/189782.jsp>`_
  overview page with links to further references.

.. rubric:: Footnotes

.. [#fusedpins] See :ref:`boardUsedPins <lang-board-values-used-pins>`
   for more information.
