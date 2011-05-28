.. highlight:: sh

.. _maple:

Maple
=====

This page is a general resource for information specific to the Maple.

.. contents:: Contents
   :local:

.. TODO [dma.rst] Ref to dma.rst in sequel instead of libmaple-dma
.. TODO [nvic.rst] Ref to nvic.rst in sequel

Technical Specifications
------------------------

* MCU: **STM32F103RBT6**, a 32-bit ARM Cortex M3 microprocessor
* Clock Speed: **72 MHz**
* **128 KB Flash** and **20 KB SRAM**
* 43 Digital I/O Pins (:ref:`gpio`)
* 15 **PWM** pins at 16 bit resolution (:ref:`pwm`)
* 15 analog input pins, 12-bit **ADC** resolution (:ref:`adc`)
* 2 **SPI** peripherals (:ref:`spi`)
* 2 **I2C** peripherals (:ref:`i2c`)
* 7 Channels of Direct Memory Access (**DMA**) (:ref:`libmaple-dma`)
* 3 **USART** peripherals (:ref:`usart`)
* One advanced and three general-purpose **timers** (:ref:`timers`)
* Dedicated **USB** port for programming and communications (:ref:`usb`)
* **JTAG** (:ref:`jtag`)
* Nested Vectored Interrupt Controller (NVIC) (including
  :ref:`external interrupt <external-interrupts>` on GPIOs)
* Supplies up to 500 mA at 3.3 V, with separate 250 mA digital and
  analog regulators for low-noise analog performance
* :ref:`Four layer design <maple-hardware>`
* Support for low power, sleep, and standby modes (<500 μA)
* Operating Voltage: 3.3 V
* Input Voltage (recommended): 4 V — 12 V
* Dimensions: 2.05″ × 2.1″

.. _maple-identify-rev:

Identifying your Rev
--------------------

We went through three versions ("Revs") of the Maple hardware: Rev 1,
Rev 3, and Rev 5 [#frev2_4]_; Rev 5, the final design, is currently on
sale.  The following sections will help you to help you identify your
Rev.

Rev 5
^^^^^

These boards went on sale in November 2010.  They have white buttons
and "r5" in small print near the "LeafLabs Maple" text next to the
"infinity leaf" logo.  The Maple Rev 5 repositioned the double header
on the right hand side to better fit 0.1 inch pitch breadboard.  This
necessitated the removal of pins 21 and 22 from the double header;
they are still available, but don't have any headers installed on
them.

.. figure:: /_static/img/maple_rev5.png
   :align: center
   :alt: Maple Rev 5

Rev 3
^^^^^

This batch of boards went on sale beginning in May 2010. They have a
darker red silkscreen and the "infinity leaf" logo.  The Maple Rev 3
was the first version which includes the built-in button, labeled BUT.

.. figure:: /_static/img/maple_rev3.png
   :align: center
   :alt: Maple Rev 3

Rev 1
^^^^^

A small number of Maple Rev 1 boards went on sale in late 2009.  They
have a light red silkscreen and a single pixelated leaf as a logo.

.. figure:: /_static/img/maple_rev1.png
   :align: center
   :alt: Maple Rev 1

.. _maple-powering:

Powering the Maple
------------------

The Maple's power source is determined by the header to the left of
the "LeafLabs" label on the silkscreen.  All versions of the Maple can
be powered from the barrel jack connector, USB, or a LiPo battery.  We
ship the Maple with a jumper on the USB selector.  In order to power
it off of an alternative source, unplug the Maple, then move the
jumper to the desired selector before reconnecting power.

You can also power the Maple via the pin labeled "Vin" on the lower
header.  This pin feeds into both the digital and analog voltage
regulators.  However, don't do this while simultaneously powering the
board from another source, or you could damage it.

.. warning:: Silkscreens on Maples up through Rev 5s manufactured in
   Spring 2011 falsely indicated that the barrel jack could be
   supplied by up to 18 V.  We recommend a barrel jack input voltage
   **no greater than 12 V**.

   See :ref:`this erratum <maple-barrel-jack>` for more information.

Using the Built-in Battery Charger
----------------------------------

Maples Rev 3 and Rev 5 also have a built-in LiPo battery charger.  In
order to use it, put a jumper across the CHRG header on the power
selection header and across the USB, or EXT selectors, depending on
whether you're charging the battery via USB cable or barrel jack
connector.  The LED labeled CHRG will light up while the battery is
being charged.  When the battery is finished charging, the LED labeled
DONE will also light up.

.. _maple-gpios:

GPIO Information
----------------

The Maple features 38 ready-to-use general purpose input/output (see
:ref:`gpio`) pins for digital input/output, numbered ``D0`` through
``D37``.  These numbers correspond to the numeric values next to each
header on the Maple silkscreen.

.. _maple-ret6-but:

Pin ``D38`` is the board's :ref:`button pin <lang-board-values-but>`.
It is thus mainly useful as an :ref:`input <lang-pin-levels>`.  The
pin will :ref:`read <lang-digitalread>` ``HIGH`` when the :ref:`button
is pressed <lang-isbuttonpressed>`.

More GPIOs (numbered ``D39``\ --``D42`` on the back of the Maple's
silkscreen) are available if you use the :ref:`lang-disabledebugports`
function; see the :ref:`board-specific debug pin constants
<lang-board-values-debug>` for more information.  (See :ref:`this
erratum <maple-nrst-pb4>` for information about the pin numbered
``43`` on the silkscreen).

.. TODO [0.1.0] silkscreen pictures which expand abbreviations

.. _maple-pin-map-master:

Master Pin Map
^^^^^^^^^^^^^^

This table shows a summary of the available functionality on every
GPIO pin, by peripheral type.  The "5 V?" column documents whether or
not the pin is :ref:`5 volt tolerant <gpio-5v-tolerant>`.

.. csv-table::
   :header: Pin, :ref:`GPIO <gpio>`, :ref:`ADC <adc>`, :ref:`Timer <timers>`, :ref:`I2C <i2c>`, :ref:`UART <usart>`, :ref:`SPI <spi>`, 5 V?

   D0,  PA3,  CH3,  2_CH4,     -,       2_RX,  -,      -
   D1,  PA2,  CH2,  2_CH3,     -,       2_TX,  -,      -
   D2,  PA0,  CH0,  2_CH1_ETR, -,       2_CTS, -,      -
   D3,  PA1,  CH1,  2_CH2,     -,       2_RTS, -,      -
   D4,  PB5,  -,    -,         1_SMBA,  -,     -,      -
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
   D25, PD2,  -,    3_ETR,     -,       -,     -,      Yes
   D26, PC10, -,    -,         -,       -,     -,      Yes
   D27, PB0,  CH8,  3_CH3,     -,       -,     -,      -
   D28, PB1,  CH9,  3_CH4,     -,       -,     -,      -
   D29, PB10, -,    -,         2_SCL,   3_TX,  -,      Yes
   D30, PB11, -,    -,         2_SDA,   3_RX,  -,      Yes
   D31, PB12, -,    -,         2_SMBA,  3_CK,  2_NSS,  Yes
   D32, PB13, -,    -,         -,       3_CTS, 2_SCK,  Yes
   D33, PB14, -,    -,         -,       3_RTS, 2_MISO, Yes
   D34, PB15, -,    -,         -,       -,     2_MOSI, Yes
   D35, PC6,  -,    -,         -,       -,     -,      Yes
   D36, PC7,  -,    -,         -,       -,     -,      Yes
   D37, PC8,  -,    -,         -,       -,     -,      Yes
   D38, PC9,  -,    -,         -,       -,     -,      Yes
   D39, PA13, -,    -,         -,       -,     -,      Yes
   D40, PA14, -,    -,         -,       -,     -,      Yes
   D41, PA15, -,    -,         -,       -,     -,      Yes
   D42, PB3,  -,    -,         -,       -,     -,      Yes

.. _maple-timer-map:

Timer Pin Map
^^^^^^^^^^^^^

The following table shows what pins are associated with a particular
timer's capture/compare channels.

.. csv-table::
   :header: Timer, Ch. 1, Ch. 2, Ch. 3, Ch. 4
   :delim: |

   1 | D6  | D7  | D8  | -
   2 | D2  | D3  | D1  | D0
   3 | D12 | D11 | D27 | D28
   4 | D5  | D9  | D14 | D24

.. _maple-exti-map:

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

.. _maple-usart-map:

USART Pin Map
^^^^^^^^^^^^^

The Maple has three serial ports (also known as USARTs): ``Serial1``,
``Serial2``, and ``Serial3``. They communicate using the pins
summarized in the following table:

.. csv-table::
   :header: Serial Port, TX, RX, CK, CTS, RTS
   :delim: |

   ``Serial1`` | 7  | 8  | 6  | -  | -
   ``Serial2`` | 1  | 0  | 10 | 2  | 3
   ``Serial3`` | 29 | 30 | 31 | 32 | 33

.. _maple-adc-bank:

Low-Noise ADC Pins
^^^^^^^^^^^^^^^^^^

The six pins at the bottom right of the board (D15—D20) generally
offer lower-noise ADC performance than other pins on the board. If
you’re concerned about getting good ADC readings, we recommend using
one of these pins to take your measurements.

Maple has an electrically isolated analog power plane with its own
regulator, and a geometrically isolated ground plane. Pins D15—D20 are
laid out to correspond with these analog planes, and our measurements
indicate that they generally have the lowest noise of all the analog
lines.  However, analog performance may vary depending upon the
activity of the other GPIOs.  Consult the :ref:`Maple hardware design
files <maple-hardware>` for more details.

Board-Specific Values
---------------------

This section lists the Maple's :ref:`board-specific values
<lang-board-values>`.

- ``CYCLES_PER_MICROSECOND``: 72
- ``BOARD_BUTTON_PIN``: 38
- ``BOARD_LED_PIN``: 13
- ``BOARD_NR_GPIO_PINS``: 44 (however, :ref:`pin D43 is not usable
  <maple-nrst-pb4>`)
- ``BOARD_NR_PWM_PINS``: 15
- ``boardPWMPins``: 0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 24, 27, 28
- ``BOARD_NR_ADC_PINS``: 15
- ``boardADCPins``: 0, 1, 2, 3, 10, 11, 12, 15, 16, 17, 18, 19, 20, 27, 28
- ``BOARD_NR_USED_PINS``: 7
- ``boardUsedPins``: ``BOARD_LED_PIN``, ``BOARD_BUTTON_PIN``,
  ``BOARD_JTMS_SWDIO_PIN``, ``BOARD_JTCK_SWCLK_PIN``,
  ``BOARD_JTDI_PIN``, ``BOARD_JTDO_PIN``, ``BOARD_NJTRST_PIN``
- ``BOARD_NR_USARTS``: 3
- ``BOARD_USART1_TX_PIN``: 7
- ``BOARD_USART1_RX_PIN``: 8
- ``BOARD_USART2_TX_PIN``: 1
- ``BOARD_USART2_RX_PIN``: 0
- ``BOARD_USART3_TX_PIN``: 29
- ``BOARD_USART3_RX_PIN``: 30
- ``BOARD_NR_SPI``: 2
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
- ``BOARD_NJTRST_PIN``: :ref:`43 <maple-nrst-pb4>`

.. _maple-hardware:

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple GitHub repository <https://github.com/leaflabs/maple>`_.  The
design files for Rev 1, Rev 3, and Rev 5 are respectively in the
``maple-r1``, ``maple-r3``, and ``maple-r5`` subdirectories.  A
schematic for a JTAG adapter suitable for use with Maple is available
in the ``jtagadapter`` directory.

From the GitHub repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `Git <http://git-scm.com/>`_, you can also clone the repository
at the command line with ::

    $ git clone git://github.com/leaflabs/maple.git

.. _maple-failure-modes:

Failure Modes
-------------

The following are known failure modes.  The failure modes aren't
design errors, but are easy ways to break or damage your board
permanently.

* **High voltage on non-tolerant pins**: not all header pins are 5V
  compatible; so e.g. connecting certain serial devices in the wrong
  way could over-voltage the pins.  The :ref:`pin-mapping master table
  <maple-pin-map-master>` details which pins are :ref:`5 V tolerant
  <gpio-5v-tolerant>`.

Errata
------

This section documents design flaws and other errors.

General
^^^^^^^

.. _maple-barrel-jack:

* **Barrel jack power supply voltage mistake**: The acceptable voltage
  range given next to the barrel jack on the Maple through Rev 5s
  manufactured in Spring 2011 is **incorrect**.  The given range is 7
  V — 18 V.  In fact, **18 V is too high** and should not be supplied
  to your board.  The recommended maximum voltage you should apply is
  **12 V**.

  The original voltage regulators used on the Maple were rated up to
  18 V.  However, the voltage regulators on current Maple Revs are
  rated up to 16 V.  Our tests indicate that they operate correctly
  through 12 V.  We do not recommend higher input voltages.

.. _maple-nrst-pb4:

* **Reset and PB4 tied together**: The Maple's reset line is also
  connected to PB4, which is labeled on the silkscreen as pin 43.
  Thus, attempting to use pin 43 as a GPIO can reset your board.  This
  has other implications.  Since PB4 is also the JTAG NJTRST line,
  this prevents the :ref:`JTAG <jtag>` "reset halt" command from
  working properly.

.. _maple-power-supply:

* **Power supply marketing mistake**: We originally sold the Maple
  advertising that it was capable of supplying up to 800 mA; the
  correct value is 500 mA.

.. _maple-pwm-marketing:

* **PWM marketing mistake**: We originally advertised the Maple as
  having 22 PWM-capable pins; the correct number is 15.

.. _maple-adc-marketing:

* **ADC marketing mistake**: We originally advertised the Maple as
  having 16 analog input pins.  Due to :ref:`the following issue
  <maple-adc-led>`, the correct number is 15.

.. _maple-adc-led:

* **ADC on BOARD_LED_PIN**: We originally sold the Maple RET6 Edition
  advertising 16 analog input lines.  However, one of them (the one on
  pin 13) is also connected to the built-in LED.  The voltage drop
  across the LED means that the analog to digital converter on that
  pin is not really useful.  While it is still usable, its readings
  will be incorrect.


By Rev
^^^^^^

The following subsections lists known issues and warnings for each
revision of the Maple board.

Rev 5
~~~~~

* **Pin 3 AIN missing**: Pin 3 is capable of analog input, but on Rev
  5s manufactured during Fall 2010, the corresponding "AIN" is missing
  from its silkscreen.  This mistake was fixed in later manufacturing
  runs.

Rev 3
~~~~~

* **Pin 3 AIN missing**: Pin 3 is capable of analog input, but the
  corresponding "AIN" is missing from the Rev 3 silkscreen.

.. _maple-rev3-bad-buttons:

* **Bad/Sticky Buttons**: a number of Rev 3 boards sold in May-June 2010
  have questionable RESET and BUT buttons.

  What seems to have happened is that the flux remover we used to
  clean the boards before shipping eroded the plastic internals, which
  resulted in intermittent functionality. All buttons on all shipped
  boards did function in testing, but some may have been unreliable in
  regular use.

  If you have this problem, we will be happy to ship you new buttons
  if you think you can re-solder them yourself, or you can ship us
  your board and we will swap out that part.

  For reference, the button part number is KMR211GLFS and the flux
  remover we used is "Precision Electronics Cleaner" from RadioShack,
  which is "Safe on most plastics" and contains Dipropylene glycol
  monomethyl ether, hydrotreated heavy naphtha, dipropylene glycol
  methyl ether acetate, and carbon dioxide.

* **Resistors on pins 0 and 1**: these header pins, which are RX/TX on
  USART2 (:ref:`Serial2 <lang-serial>`), have resistors in-line
  between the STM32 and the headers. These resistors increase the
  impedance of the lines for ADC reads and affect the open drain GPIO
  functionality of the pins.

  These resistors were accidentally copied over from older Arduino USB
  designs, where they appear to protect the USB-Serial converter from
  TTL voltage on the headers.

* **Silkscreen Errors**: the silkscreen on the bottom indicated PWM
  functionality on pin 25 and listen the external header GND pin as
  number 38 (actually 38 is connected to the BUT button). We manually
  sharpied over both of these mistakes.

Rev 1
~~~~~

* **ADC noise**: generally very high, in particular when the USB port
  is being used for communications (including keep-alive pings when
  connected to a computer).

  This issue was resolved in Rev 3 with a 4-layer design and a
  :ref:`geometrically isolated ADC Vref plane <maple-adc-bank>`.

* **Resistors on pins 0 and 1**: these header pins, which are RX/TX on
  USART2 (:ref:`Serial2 <lang-serial>`), have resistors in-line
  between the STM32 and the headers. These resistors increase the
  impedance of the lines for ADC reads and affect the open drain GPIO
  functionality of the pins.

  These resistors were accidentally copied over from older Arduino USB
  designs, where they appear to protect the USB-Serial converter from
  TTL voltage on the headers.

* **Silkscreen Differences**: the pin numbering scheme on Rev 1 is
  different from Rev 3, and thus Rev 3 software is difficult to use
  with Rev 1 boards. Notably, the analog input bank is labeled A0-A4
  on Rev 1 but 15-20 on Rev 3, and the extra header bank does not have
  a pinout table on the bottom.

* **No BUT Button**: the BUT button, useful for serial bootloading,
  was only added in Rev 3. As a workaround, you can directly short the
  appropriate MCU pin to Vcc; see `this forum posting
  <http://forums.leaflabs.com/topic.php?id=32#post-126>`_.

Recommended Reading
-------------------

STMicro documentation for STM32F103RB microcontroller:

* `Datasheet
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00161566.pdf>`_
  (PDF); covers STM32F103x8, STM32F103xB.
* `Reference Manual RM0008
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/CD00171190.pdf>`_
  (PDF); general, definitive resource for STM32F1 line.
* `Programming Manual PM0056
  <http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/PROGRAMMING_MANUAL/CD00228163.pdf>`_
  (PDF); assembly language and register reference.
* `STM32F103RB <http://www.st.com/internet/mcu/product/164487.jsp>`_
  overview page with links to further references.

.. rubric:: Footnotes

.. [#frev2_4] Revs 2 and 4 were prototypes that didn't pass internal
   testing.
