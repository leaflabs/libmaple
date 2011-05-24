.. highlight:: sh

.. _maple-ret6:

Maple RET6 Edition
==================

.. contents:: Contents
   :local:

Technical Specifications
------------------------

    * MCU: **STM32F103RET6**, a 32-bit ARM Cortex M3 microprocessor
    * Clock Speed: **72 MHz**
    * **512KB Flash** and **64KB SRAM**
    * 43 Digital I/O Pins (:ref:`GPIO <gpio>`)
    * 16 Analog Input pins, 12 bit **ADC** resolution (:ref:`ADC
      <adc>`)
    * Built-in, 2 channel **DAC** at 12 bit resolution
      (:ref:`libmaple-dac`).
    * 19 **PWM** pins at 16-bit resolution (:ref:`PWM <pwm>`)
    * Dedicated **USB** port for programming and communications
      (:ref:`USB<usb>`)
    * External **JTAG** interface (:ref:`JTAG <jtag>`)
    * 64 Channel nested vector interrupt handler (including
      :ref:`external interrupt <lang-attachinterrupt>` on GPIOs)
    * Integrated **SPI** (:ref:`SPI <spi>`)
    * Integrated **SDIO**
    * Integrated **I2C** and **I2S** (:ref:`I2C <i2c>`)
    * 12 Channels of Direct Memory Access (**DMA**)
      (:ref:`libmaple-dma`)
    * 3 **USART** and 2 **UART** devices (:ref:`USART <usart>`)
    * Two advanced control, four general purpose, two basic **timers**
      (:ref:`timers`)
    * Supplies up to 500mA @ 3.3v (with separate 250 mA digital and
      analog regulators)
    * Support for low power, sleep, and standby modes (<500uA)
    * Operating Voltage: 3.3V
    * Input Voltage (recommended): 3V-12V
    * Dimensions are 2.05″x2.1″

.. _maple-ret6-powering:

Powering the Maple RET6 Edition
-------------------------------

The Maple RET6 Edition's power source is determined by the header to
the left of the "LeafLabs" label on the silkscreen.  The RET6 Edition
can be powered from the barrel jack connector, USB, or a LiPo battery.
We ship the RET6 Edition with a jumper on the USB selector.  In order
to power it off of an alternative source, unplug the board, then move
the jumper to the desired selector before reconnecting power.

You can also power the Maple via the pin labeled "Vin" on the lower
header.  However, don't do this while simultaneously powering the
board from another source, or you could damage the board.

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

More GPIOs (numbered ``D39``\ --``D42``) are available if you use the
:ref:`lang-disabledebugports` function; see the :ref:`board-specific
debug pin constants <lang-board-values-debug>` for more information.
(See :ref:`this erratum <maple-ret6-nrst-pb4>` for information about
the pin numbered ``43`` on the silkscreen).

.. TODO [0.1.0] silkscreen pictures which expand abbreviations

.. _maple-ret6-pin-map-master:

Master Pin Map
^^^^^^^^^^^^^^

This table shows the available functionality on every GPIO pin, by
peripheral type. The "STM32" column refers to the port and number that
the header is connected to on the microcontroller.  The "5V?" column
documents whether or not the pin is 5 volt tolerant.

.. csv-table::
   :header: Pin, STM32, :ref:`ADC <adc>`, :ref:`Timer <timers>`, :ref:`I2C <i2c>`, :ref:`UART <usart>`, :ref:`SPI <spi>`, 5v?

   D0,  PA3,  ADC3,  TIM2_CH4,     -,          USART2_RX,  -,         -
   D1,  PA2,  ADC2,  TIM2_CH3,     -,          USART2_TX,  -,         -
   D2,  PA0,  ADC0,  TIM2_CH1_ETR, -,          USART2_CTS, -,         -
   D3,  PA1,  ADC1,  TIM2_CH2,     -,          USART2_RTS, -,         -
   D4,  PB5,  -,     -,            ISC1_SMBA,  -,          SPI3_MOSI, -
   D5,  PB6,  -,     TIM4_CH1,     I2C1_SCL,   -,          -,         Yes
   D6,  PA8,  -,     TIM1_CH1,     -,          USART1_CK,  -,         Yes
   D7,  PA9,  -,     TIM1_CH2,     -,          USART1_TX,  -,         Yes
   D8,  PA10, -,     TIM1_CH3,     -,          USART1_RX,  -,         Yes
   D9,  PB7,  -,     TIM4_CH2,     I2C1_SDA,   -,          -,         Yes
   D10, PA4,  ADC4,  -,            -,          USART2_CK,  SPI1_NSS,  -
   D11, PA7,  ADC7,  TIM3_CH2,     -,          -,          SPI1_MOSI, -
   D12, PA6,  ADC6,  TIM3_CH1,     -,          -,          SPI1_MISO, -
   D13, PA5,  ADC5,  -,            -,          -,          SPI1_SCK,  -
   D14, PB8,  -,     TIM4_CH3,     -,          -,          -,         Yes
   D15, PC0,  ADC10, -,            -,          -,          -,         -
   D16, PC1,  ADC11, -,            -,          -,          -,         -
   D17, PC2,  ADC12, -,            -,          -,          -,         -
   D18, PC3,  ADC13, -,            -,          -,          -,         -
   D19, PC4,  ADC14, -,            -,          -,          -,         -
   D20, PC5,  ADC15, -,            -,          -,          -,         -
   D21, PC13, -,     -,            -,          -,          -,         -
   D22, PC14, -,     -,            -,          -,          -,         -
   D23, PC15, -,     -,            -,          -,          -,         -
   D24, PB9,  -,     TIM4_CH4,     -,          -,          -,         Yes
   D25, PD2,  -,     TIM3_ETR,     -,          -,          UART5_RX,  Yes
   D26, PC10, -,     -,            -,          -,          UART4_TX,  Yes
   D27, PB0,  ADC8,  TIM3_CH3,     -,          -,          -,         -
   D28, PB1,  ADC9,  TIM3_CH4,     -,          -,          -,         -
   D29, PB10, -,     -,            I2C2_SCL,   USART3_TX,  -,         Yes
   D30, PB11, -,     -,            I2C2_SDA,   USART3_RX,  -,         Yes
   D31, PB12, -,     TIM1_BKIN,    I2C2_SMBA,  USART3_CK,  SPI2_NSS,  Yes
   D32, PB13, -,     TIM1_CH1N,    -,          USART3_CTS, SPI2_SCK,  Yes
   D33, PB14, -,     TIM1_CH2N,    -,          USART3_RTS, SPI2_MISO, Yes
   D34, PB15, -,     TIM1_CH3N,    -,          -,          SPI2_MOSI, Yes
   D35, PC6,  -,     TIM8_CH1,     -,          -,          -,         Yes
   D36, PC7,  -,     TIM8_CH2,     -,          -,          -,         Yes
   D37, PC8,  -,     TIM8_CH3,     -,          -,          -,         Yes
   D38, PC9,  -,     TIM8_CH4,     -,          -,          -,         Yes
   D39, PA13, -,     -,            -,          -,          -,         Yes
   D40, PA14, -,     -,            -,          -,          -,         Yes
   D41, PA15, -,     -,            -,          -,          SPI3_NSS,  Yes
   D42, PB3,  -,     -,            -,          -,          SPI3_SCK,  Yes

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
     - 0, 18
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
     - 21, 32
   * - EXTI14
     - 22, 33
   * - EXTI15
     - 23, 34

.. _maple-ret6-usart-map:

USART Pin Map
^^^^^^^^^^^^^

The Maple RET6 Edition has three serial ports whose pins are broken
out to headers (also known as a UARTs or USARTs): ``Serial1``,
``Serial2``, and ``Serial3``. They communicate using the pins
summarized in the following table:

.. csv-table::
   :header: Serial Port, TX, RX, CK, CTS, RTS
   :delim: |

   ``Serial1`` | 7  | 8  | 6  | -  | -
   ``Serial2`` | 1  | 0  | 10 | 2  | 3
   ``Serial3`` | 29 | 30 | 31 | 32 | 33

Unfortunately, :ref:`UART4 and UART5 aren't completely available
<maple-ret6-uart-errata>`.

Board-Specific Values
---------------------

This section lists the Maple RET6 Edition's :ref:`board-specific
values <lang-board-values>`.

- ``CYCLES_PER_MICROSECOND``: 72
- ``BOARD_BUTTON_PIN``: 38
- ``BOARD_LED_PIN``: 13
- ``BOARD_NR_GPIO_PINS``: 44
- ``BOARD_NR_PWM_PINS``: 16
- ``boardPWMPins``: 0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 24, 25, 27, 28
- ``BOARD_NR_ADC_PINS``: 15
- ``boardADCPins``: 0, 1, 2, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 27, 28
- ``BOARD_NR_USED_PINS``: 7
- ``boardUsedPins``: ``BOARD_LED_PIN``, ``BOARD_BUTTON_PIN``,
  ``BOARD_JTMS_SWDIO_PIN``, ``BOARD_JTCK_SWCLK_PIN``,
  ``BOARD_JTDI_PIN``, ``BOARD_JTDO_PIN``, ``BOARD_NJTRST_PIN``
- ``BOARD_NR_USARTS``: 3 (unfortunately, due to the Maple Rev 5
  design, UARTs 4 and 5 have pins which are not broken out)
- ``BOARD_USART1_TX_PIN``: 7
- ``BOARD_USART1_RX_PIN``: 8
- ``BOARD_USART2_TX_PIN``: 1
- ``BOARD_USART2_RX_PIN``: 0
- ``BOARD_USART3_TX_PIN``: 29
- ``BOARD_USART3_RX_PIN``: 30
- ``BOARD_NR_SPI``: 3
- ``BOARD_SPI1_NSS_PIN``: 10
- ``BOARD_SPI1_MOSI_PIN``: 11
- ``BOARD_SPI1_MISO_PIN``: 12
- ``BOARD_SPI1_SCK_PIN``: 13
- ``BOARD_SPI2_NSS_PIN``: 31
- ``BOARD_SPI2_MOSI_PIN``: 34
- ``BOARD_SPI2_MISO_PIN``: 33
- ``BOARD_SPI2_SCK_PIN``: 32
- ``BOARD_SPI3_NSS_PIN``: 41
- ``BOARD_SPI3_MOSI_PIN``: 4
- ``BOARD_SPI3_MISO_PIN``: 43
- ``BOARD_SPI3_SCK_PIN``: 42
- ``BOARD_JTMS_SWDIO_PIN``: 39
- ``BOARD_JTCK_SWCLK_PIN``: 40
- ``BOARD_JTDI_PIN``: 41
- ``BOARD_JTDO_PIN``: 42
- ``BOARD_NJTRST_PIN``: 43

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple Github repository <https://github.com/leaflabs/maple>`_.  Other
than the processor used, the design files for the Maple RET6 edition
are identical to the Maple Rev 5, which are in the ``maple-r5``
subdirectory of the Maple repository.  A schematic for a JTAG adapter
suitable for use with Maple is available in the ``jtagadapter``
directory.

From the GitHub repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `git <http://git-scm.com/>`_, you can also clone the repository
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
  <maple-ret6-pin-map-master>` details which pins are 5V-tolerant.

Errata
------

This section lists known issues and warnings for the Maple RET6 Edition.

* **Power Supply Marketing Mistake**: We originally sold the Maple
  RET6 Edition advertising that it was capable of supplying up to 800
  mA; the correct value is 500 mA.

.. _maple-ret6-uart-errata:

* **UART4, UART5 GPIOs unavailable**: Pins related to UARTs 4 and 5
  are not broken out to headers (specifically, PC11/UART4_RX and
  PC12/UART5_TX).  The RET6 Edition's hardware layout is identical to
  that of the Maple Rev 5, which wasn't designed for use with these
  STM32F103RET6-only peripherals.

* **DAC channel 2 on BOARD_LED_PIN**: The Maple Rev 5 connects PA5 to
  the board's built-in LED; this is the same GPIO bit which is
  connected to the DAC's channel 2 output.  This is also due to the
  RET6 Edition's board layout being copied from the base Maple Rev 5.

.. _maple-ret6-nrst-pb4:

* **Reset and PB4 tied together**: The Maple's reset line is also
  connected to PB4, which is labeled on the silkscreen as pin 43.
  Thus, attempting to use pin 43 as a GPIO may reset your board.  This
  has other implications.  Since PB4 is also the JTAG NJTRST line,
  this prevents the :ref:`JTAG <jtag>` "reset halt" command from
  working properly.  Also, since PB4 is SPI3_MISO, the SPI3 peripheral
  is not fully usable.

Recommended Reading
-------------------

* STMicro documentation for STM32F103RE microcontroller:

    * `Datasheet
      <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00191185.pdf>`_ (PDF)
    * `Reference Manual
      <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (PDF)
    * `Programming Manual
      <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_
      (PDF; assembly language and register reference)
    * `ST's STM32F103RE reference page
      <http://www.st.com/internet/mcu/product/164485.jsp>`_
