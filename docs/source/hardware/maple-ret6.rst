.. highlight:: sh

.. _maple-ret6:

Maple RET6 Edition
==================

This page is a general resource for information specific to the Maple
RET6 Edition.  The Maple RET6 Edition is a "beta" board released as a
simple way to get a more powerful chip than the one on the base Maple
(the STM32F103RET6, hence the name) in the hands of Maple developers.

.. contents:: Contents
   :local:

.. TODO [dma.rst] Ref to dma.rst in sequel instead of libmaple-dma
.. TODO [dac.rst] Ref to dac.rst in sequel instead of libmaple-dac
.. TODO [nvic.rst] Ref to nvic.rst in sequel

Technical Specifications
------------------------

* MCU: **STM32F103RET6**, a 32-bit ARM Cortex M3 microprocessor
* Clock Speed: **72 MHz**
* **512 KB Flash** and **64 KB SRAM**
* 43 Digital I/O Pins (:ref:`gpio`)
* 18 **PWM** pins at 16 bit resolution (:ref:`pwm`)
* 15 analog input pins, 12 bit **ADC** resolution (:ref:`adc`)
* Built-in, 2 channel **DAC** at 12 bit resolution (:ref:`libmaple-dac`).
* 2 **SPI** peripherals with **I2S** support (:ref:`spi`)
* 2 **I2C** peripherals (:ref:`i2c`)
* 12 Channels of Direct Memory Access (**DMA**)
  (:ref:`libmaple-dma`) with 2 DMA controllers
* 3 **USART** devices (:ref:`usart`)
* 2 advanced, 4 general-purpose, and 2 basic **timers** (:ref:`timers`)
* Dedicated **USB** port for programming and communications (:ref:`usb`)
* **JTAG** (:ref:`jtag`)
* Nested Vectored Interrupt Controller (NVIC) (including
  :ref:`external interrupt <lang-attachinterrupt>` on GPIOs)
* Supplies up to 500 mA at 3.3 V, with :ref:`separate 250 mA digital
  and analog regulators <maple-ret6-adc-bank>` for low-noise analog
  performance
* :ref:`Four layer design <maple-ret6-hardware>`
* Support for low power, sleep, and standby modes (<500 μA)
* Operating Voltage: 3.3 V
* Input Voltage (recommended): 4 V — 12 V
* Dimensions are 2.05″ × 2.1″

.. _maple-ret6-powering:

Powering the Maple RET6 Edition
-------------------------------

The Maple RET6 Edition is powered in the :ref:`same way as the
standard Maple <maple-powering>`.

.. warning:: The RET6 Edition silkscreen falsely indicates that the
   barrel jack accepts up to 18 V.  We recommend a barrel jack input
   voltage **no greater than 12 V**.

   See :ref:`this erratum <maple-barrel-jack>` for more information.

Using the Built-in Battery Charger
----------------------------------

The RET6 Edition has a built-in LiPo battery charger.  In order to use
it, put a jumper across the CHRG header on the power selection header
and across the USB, or EXT selectors, depending on whether you're
charging the battery via USB cable or barrel jack connector.  The LED
labeled CHRG will light up while the battery is being charged.  When
the battery is finished charging, the LED labeled DONE will also light
up.

.. _maple-ret6-gpios:

GPIO Information
----------------

The RET6 Edition features 38 ready-to-use general purpose input/output
(see :ref:`gpio`) pins for digital input/output, numbered ``D0``
through ``D37``.  These numbers correspond to the numeric values next
to each header on the Maple silkscreen.

.. _maple-ret6-but:

Pin ``D38`` is the board's :ref:`button pin <lang-board-values-but>`.
It is thus mainly useful as an :ref:`input <lang-pin-levels>`.  The
pin will :ref:`read <lang-digitalread>` ``HIGH`` when the :ref:`button
is pressed <lang-isbuttonpressed>`.

More GPIOs (numbered ``D39``\ --``D42`` on the back of the RET6
Edition's silkscreen) are available if you use the
:ref:`lang-disabledebugports` function; see the :ref:`board-specific
debug pin constants <lang-board-values-debug>` for more information.
(See :ref:`this erratum <maple-ret6-nrst-pb4>` for information about
the pin numbered ``43`` on the silkscreen).

.. TODO [0.1.0] silkscreen pictures which expand abbreviations

.. _maple-ret6-pin-map-master:

Master Pin Map
^^^^^^^^^^^^^^

This table shows a summary of the available functionality on every
GPIO pin, by peripheral type.  The "5 V?" column documents whether or
not the pin is :ref:`5 volt tolerant <gpio-5v-tolerant>`.

.. csv-table::
   :header: Pin, :ref:`GPIO <gpio>`, :ref:`ADC <adc>`, :ref:`Timer <timers>`, :ref:`I2C <i2c>`, :ref:`UART/USART <usart>`, :ref:`SPI <spi>`, 5 V?

   D0,  PA3,  CH3,  2_CH4,     -,       2_RX,  -,      -
   D1,  PA2,  CH2,  2_CH3,     -,       2_TX,  -,      -
   D2,  PA0,  CH0,  2_CH1_ETR, -,       2_CTS, -,      -
   D3,  PA1,  CH1,  2_CH2,     -,       2_RTS, -,      -
   D4,  PB5,  -,    -,         1_SMBA,  -,     3_MOSI, -
   D5,  PB6,  -,    4_CH1,     1_SCL,   -,     -,      Yes
   D6,  PA8,  -,    1_CH1,     -,       1_CK,  -,      Yes
   D7,  PA9,  -,    1_CH2,     -,       1_TX,  -,      Yes
   D8,  PA10, -,    1_CH3,     -,       1_RX,  -,      Yes
   D9,  PB7,  -,    4_CH2,     1_SDA,   -,     -,      Yes
   D10, PA4,  CH4,  -,         -,       2_CK,  1_NSS,  -
   D11, PA7,  CH7,  3_CH2,     -,       -,     1_MOSI, -
   D12, PA6,  CH6,  3_CH1,     -,       -,     1_MISO, -
   D13, PA5,  CH5,  -,         -,       -,     1_SCK,  -
   D14, PB8,  -,    4_CH3,     -,       -,     -,      Yes
   D15, PC0,  CH10, -,         -,       -,     -,      -
   D16, PC1,  CH11, -,         -,       -,     -,      -
   D17, PC2,  CH12, -,         -,       -,     -,      -
   D18, PC3,  CH13, -,         -,       -,     -,      -
   D19, PC4,  CH14, -,         -,       -,     -,      -
   D20, PC5,  CH15, -,         -,       -,     -,      -
   D21, PC13, -,    -,         -,       -,     -,      -
   D22, PC14, -,    -,         -,       -,     -,      -
   D23, PC15, -,    -,         -,       -,     -,      -
   D24, PB9,  -,    4_CH4,     -,       -,     -,      Yes
   D25, PD2,  -,    3_ETR,     -,       -,     5_RX,   Yes
   D26, PC10, -,    -,         -,       -,     4_TX,   Yes
   D27, PB0,  CH8,  3_CH3,     -,       -,     -,      -
   D28, PB1,  CH9,  3_CH4,     -,       -,     -,      -
   D29, PB10, -,    -,         2_SCL,   3_TX,  -,      Yes
   D30, PB11, -,    -,         2_SDA,   3_RX,  -,      Yes
   D31, PB12, -,    1_BKIN,    2_SMBA,  3_CK,  2_NSS,  Yes
   D32, PB13, -,    1_CH1N,    -,       3_CTS, 2_SCK,  Yes
   D33, PB14, -,    1_CH2N,    -,       3_RTS, 2_MISO, Yes
   D34, PB15, -,    1_CH3N,    -,       -,     2_MOSI, Yes
   D35, PC6,  -,    8_CH1,     -,       -,     -,      Yes
   D36, PC7,  -,    8_CH2,     -,       -,     -,      Yes
   D37, PC8,  -,    8_CH3,     -,       -,     -,      Yes
   D38, PC9,  -,    8_CH4,     -,       -,     -,      Yes
   D39, PA13, -,    -,         -,       -,     -,      Yes
   D40, PA14, -,    -,         -,       -,     -,      Yes
   D41, PA15, -,    -,         -,       -,     3_NSS,  Yes
   D42, PB3,  -,    -,         -,       -,     3_SCK,  Yes

.. _maple-ret6-timer-map:

Timer Pin Map
^^^^^^^^^^^^^

The following table shows what pins are associated with a particular
timer's capture/compare channels.  Note that timer 5's channels share
pins with timer 2 (e.g., timer 5 channel 1 is also available on D2,
channel 2 on D3, etc.).

.. csv-table::
   :header: Timer, Ch. 1, Ch. 2, Ch. 3, Ch. 4
   :delim: |

   1 | D6  | D7  | D8  | -
   2 | D2  | D3  | D1  | D0
   3 | D12 | D11 | D27 | D28
   4 | D5  | D9  | D14 | D24
   8 | D35 | D36 | D37 | :ref:`D38 <maple-ret6-but>`

.. _maple-ret6-exti-map:

EXTI Line Pin Map
^^^^^^^^^^^^^^^^^

The following table shows which pins connect to which :ref:`EXTI lines
<external-interrupts-exti-line>` on the Maple RET6 Edition.

.. list-table::
   :widths: 1 1
   :header-rows: 1

   * - EXTI Line
     - Pins
   * - EXTI0
     - 2, 15, 27
   * - EXTI1
     - 3, 16, 28
   * - EXTI2
     - 1, 17, 25
   * - EXTI3
     - 0, 18, 42
   * - EXTI4
     - 10, 19
   * - EXTI5
     - 4, 13, 20
   * - EXTI6
     - 5, 12, 35
   * - EXTI7
     - 9, 11, 36
   * - EXTI8
     - 6, 14, 37
   * - EXTI9
     - 7, 25, 28
   * - EXTI10
     - 8, 26, 29
   * - EXTI11
     - 30
   * - EXTI12
     - 31
   * - EXTI13
     - 21, 32, 39
   * - EXTI14
     - 22, 33, 40
   * - EXTI15
     - 23, 34, 41

.. _maple-ret6-usart-map:

USART Pin Map
^^^^^^^^^^^^^

The Maple RET6 Edition has three serial ports whose pins are broken
out to headers (also known as :ref:`USARTs <usart>`). They communicate
using the pins summarized in the following table:

.. csv-table::
   :header: Serial Port, TX, RX, CK, CTS, RTS
   :delim: |

   ``Serial1`` | 7  | 8  | 6  | -  | -
   ``Serial2`` | 1  | 0  | 10 | 2  | 3
   ``Serial3`` | 29 | 30 | 31 | 32 | 33

Unfortunately, :ref:`UART4 and UART5 aren't completely available
<maple-ret6-uarts>`.

.. _maple-ret6-adc-bank:

Low-Noise ADC Pins
^^^^^^^^^^^^^^^^^^

The six pins at the bottom right of the board (D15—D20) generally
offer lower-noise ADC performance than other pins on the board. If
you’re concerned about getting good ADC readings, we recommend using
one of these pins to take your measurements.  More details in the
:ref:`Maple hardware documentation <maple-adc-bank>`.

Board-Specific Values
---------------------

This section lists the Maple RET6 Edition's :ref:`board-specific
values <lang-board-values>`.

- ``CYCLES_PER_MICROSECOND``: 72
- ``BOARD_BUTTON_PIN``: 38
- ``BOARD_LED_PIN``: 13
- ``BOARD_NR_GPIO_PINS``: 44 (however, :ref:`pin D43 is not usable
  <maple-nrst-pb4>`)
- ``BOARD_NR_PWM_PINS``: 18
- ``boardPWMPins``: 0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 24, 27, 28,
  35, 36, 37
- ``BOARD_NR_ADC_PINS``: 15
- ``boardADCPins``: 0, 1, 2, 3, 10, 11, 12, 15, 16, 17, 18, 19, 20, 27, 28
- ``BOARD_NR_USED_PINS``: 7
- ``boardUsedPins``: ``BOARD_LED_PIN``, ``BOARD_BUTTON_PIN``,
  ``BOARD_JTMS_SWDIO_PIN``, ``BOARD_JTCK_SWCLK_PIN``,
  ``BOARD_JTDI_PIN``, ``BOARD_JTDO_PIN``, ``BOARD_NJTRST_PIN``
- ``BOARD_NR_USARTS``: 3 (unfortunately, :ref:`due to the Maple Rev 5
  design <maple-ret6-uarts>`, UARTs 4 and 5 have pins which are not
  broken out).
- ``BOARD_USART1_TX_PIN``: 7
- ``BOARD_USART1_RX_PIN``: 8
- ``BOARD_USART2_TX_PIN``: 1
- ``BOARD_USART2_RX_PIN``: 0
- ``BOARD_USART3_TX_PIN``: 29
- ``BOARD_USART3_RX_PIN``: 30
- ``BOARD_NR_SPI``: 2 (unfortunately, :ref:`due to the Maple Rev 5
  design <maple-ret6-nrst-pb4>`, SPI3 is unavailable).
- ``BOARD_SPI1_NSS_PIN``: 10
- ``BOARD_SPI1_MOSI_PIN``: 11
- ``BOARD_SPI1_MISO_PIN``: 12
- ``BOARD_SPI1_SCK_PIN``: 13
- ``BOARD_SPI2_NSS_PIN``: 31
- ``BOARD_SPI2_MOSI_PIN``: 34
- ``BOARD_SPI2_MISO_PIN``: 33
- ``BOARD_SPI2_SCK_PIN``: 32
- ``BOARD_JTMS_SWDIO_PIN``: 39
- ``BOARD_JTCK_SWCLK_PIN``: 40
- ``BOARD_JTDI_PIN``: 41
- ``BOARD_JTDO_PIN``: 42
- ``BOARD_NJTRST_PIN``: :ref:`43 <maple-ret6-nrst-pb4>`

.. _maple-ret6-hardware:

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple GitHub repository <https://github.com/leaflabs/maple>`_.  Other
than the processor used, the design files for the Maple RET6 edition
are identical to the Maple Rev 5, which are in the ``maple-r5``
subdirectory of the Maple repository.  A schematic for a JTAG adapter
suitable for use with Maple is available in the ``jtagadapter``
directory.

From the GitHub repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `Git <http://git-scm.com/>`_, you can also clone the repository
at the command line with ::

    $ git clone git://github.com/leaflabs/maple.git

.. _maple-ret6-failure-modes:

Failure Modes
-------------

The following known failure modes apply to all Maple boards.  The
failure modes aren't design errors, but are easy ways to break or
damage your board permanently.

* **High voltage on non-tolerant pins**: not all header pins are 5V
  compatible; so e.g. connecting certain serial devices in the wrong
  way could over-voltage the pins.  The :ref:`pin-mapping master table
  <maple-ret6-pin-map-master>` details which pins are
  :ref:`5V-tolerant <gpio-5v-tolerant>`.

Errata
------

This section lists known issues and warnings for the Maple RET6
Edition.  Some of these are simply due to the RET6 Edition using the
Maple's circuit board, which was not designed to accomodate extra
features only available on the STM32F103RET6.

.. _maple-ret6-barrel-jack:

* **Barrel jack power supply voltage mistake**: The silkscreen next to
  the barrel jack connector incorrectly indicates that up to an 18 V
  input voltage is allowed.  **We do not recommend exceeding 12 V**.

  See this :ref:`Maple erratum <maple-barrel-jack>` for more
  information.

* **Power supply marketing mistake**: We originally sold the Maple
  RET6 Edition advertising that it was capable of supplying up to 800
  mA; the correct value is 500 mA.

.. _maple-ret6-uarts:

* **UART4, UART5 GPIOs unavailable**: Pins related to UARTs 4 and 5
  are not broken out to headers (specifically, PC11/UART4_RX and
  PC12/UART5_TX).  This is due to the RET6 Edition's board layout
  being that of the Maple Rev 5, which was not designed with these
  RET6-specific features in mind.

.. _maple-ret6-dac-ch2:

* **DAC channel 2 on BOARD_LED_PIN**: The Maple Rev 5 connects PA5 to
  the board's built-in LED; this is the same GPIO bit which is
  connected to the DAC's channel 2 output.  This is also due to the
  RET6 Edition's board layout being that of the Maple Rev 5.  The DAC
  output channel is still available, and (if you use libmaple) its
  output is buffered by default, so this may not significantly
  interfere with its functionality.

.. _maple-ret6-nrst-pb4:

* **Reset and PB4 tied together**: The RET6 Edition's reset line is
  also connected to PB4, which is labeled on the silkscreen as pin 43.
  Thus, attempting to use pin 43 as a GPIO can reset your board.  This
  has other implications.  Since PB4 is also the JTAG NJTRST line,
  this prevents the :ref:`JTAG <jtag>` "reset halt" command from
  working properly.  Also, since PB4 is SPI3_MISO, the SPI3 peripheral
  is not fully usable.

.. _maple-ret6-sdio:

* **SDIO lines not broken out**: The RET6 Edition's SDIO peripheral is
  not usable, as some of its data lines are either not broken out or
  used for other purposes.  This is also due to the RET6 Edition's
  board layout being that of the Maple Rev 5.

.. _maple-ret6-adc-led:

* **ADC on BOARD_LED_PIN**: We originally sold the Maple RET6 Edition
  advertising 16 analog input lines.  However, one of them (the one on
  pin 13) is also connected to the built-in LED.  The voltage drop
  across the LED means that the analog to digital converter on that
  pin is not really useful.  While it is still usable, its readings
  will be incorrect.

Recommended Reading
-------------------

STMicro documentation for STM32F103RE microcontroller:

* `Datasheet
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00191185.pdf>`_
  (PDF); covers STM32F103xC, STM32F103xD, STM32F103xE.
* `Reference Manual RM0008
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf>`_
  (PDF); general, definitive resource for STM32F1 line.
* `Programming Manual PM0056
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/PROGRAMMING_MANUAL/CD00228163.pdf>`_
  (PDF); assembly language and register reference.
* `STM32F103RE <http://www.st.com/internet/mcu/product/164485.jsp>`_
  overview page with links to further references.
