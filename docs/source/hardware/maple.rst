.. highlight:: sh

.. _hardware-maple:

Maple
=====

.. contents:: Contents
   :local:

Technical Specifications
------------------------

    * MCU: **STM32F103RBT6**, a 32-bit ARM Cortex M3 microprocessor
    * Clock Speed: **72 MHz**
    * Operating Voltage: 3.3V
    * Input Voltage (recommended): 3V-12V
    * 39 Digital I/O Pins (:ref:`GPIO <gpio>`)
    * 16 Analog Input Pins 
    * 12-bit **ADC** resolution (:ref:`ADC <adc>`)
    * 15 **PWM** pins at 16-bit resolution (:ref:`PWM <pwm>`)
    * Dedicated **USB** port for programming and communications (:ref:`USB<usb>`)
    * External **JTAG** interface (:ref:`USB <jtag>`)
    * **128 Flash** and **20KB SRAM**
    * 64 Channel nested vector interrupt handler (including external interrupt on GPIOs)
    * Integrated **SPI** (:ref:`SPI<spi>`)
    * Integrated **I2C** (:ref:`I2C<i2c>`)
    * 7 Channels of Direct Memory Access (**DMA**)
    * 3 **USART** divices (:ref:`USART <usart>`)
    * Four 4-channel **timers** (:ref:`Timers <timers>`)
    * Supplies up to 800mA @ 3.3v
    * Support for low power and sleep modes (<500uA)
    * Dimensions are 2.05″x2.1″

.. _maple-hardware-identify-rev:

Identifying your Rev
--------------------

We went through three versions ("Revs") of the Maple hardware: Rev 1,
Rev 3, and Rev 5 [#frev2_4]_; Rev 5, the final design, is currently on
sale.  The following sections will help you to help you identify your
Rev.

Rev 5
^^^^^

These boards went on sale in November 2010.  They have white buttons,
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
It also includes a built-in LiPo battery charger.

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

.. _hardware-maple-powering:

Powering the Maple
------------------

The Maple's power source is determined by the header to the left of
the "LeafLabs" label on the silkscreen.  All versions of the Maple can
be powered from the barrel jack connector, USB, or a LiPo battery.  We
ship the Maple with a jumper on the USB selector.  In order to power
it off of an alternative source, unplug the Maple, then move the
jumper to the desired selector before reconnecting power.

You can also power the Maple via the pin labeled "Vin" on the lower
header.  However, don't do this while simultaneously powering the
Maple from another source, or you could damage the board.

Using the Built-in Battery Charger
----------------------------------

Maples Rev 3 and Rev 5 also have a built-in LiPo battery charger.  In
order to use it, put a jumper across the CHRG header on the power
selection header and across the USB, or EXT selectors, depending on
whether you're charging the battery via USB cable or barrel jack
connector.  The LED labeled CHRG will light up while the battery is
being charged.  When the battery is finished charging, the LED labeled
DONE will also light up.

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple github repository <https://github.com/leaflabs/maple>`_.  The
design files for Rev 1, Rev 3, and Rev 5 are respectively in the
``maple-r1``, ``maple-r3``, and ``maple-r5`` subdirectories.  A
schematic for a JTAG adapter suitable for use with Maple is available
in the ``jtagadapter`` directory.

From the github repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `git <http://git-scm.com/>`_, you can also clone the repository
at the command line with ::

    $ git clone git://github.com/leaflabs/maple.git

.. _maple-failure-modes:

Failure Modes
-------------

The following known failure modes apply to all Maple versions.  The
failure modes aren't design errors, but are easy ways to break or
damage your board permanently.

* **High voltage on non-tolerant pins**: not all header pins are 5V
  compatible; so e.g. connecting certain serial devices in the wrong
  way could over-voltage the pins.  The :ref:`Pin-Mapping Mega Table
  <pin-mapping-mega-table>` details which pins are 5V-tolerant.

Errata
------

This section lists known issues and warnings for each revision of the
Maple board.

Rev 5
^^^^^
Known issues:

* **Pin 3 AIN missing**: Pin 3 is capable of analog input, but on
  boards sold in during Fall 2010, the corresponding "AIN" is missing
  from its silkscreen.  This mistake was fixed in later manufacturing
  runs.

Rev 3
^^^^^

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

* **PWM Marketing Mistake**: We originally sold the Maple advertising
  22 channels of 16-bit hardware PWM; actually the Maple only has 15.

Rev 1
^^^^^

* **ADC noise**: generally very high, in particular when the USB port
  is being used for communications (including keep-alive pings when
  connected to a computer).

  This issue was resolved in Rev 3 with a 4-layer design and a
  geometrically isolated ADC V\ :sub:`ref` plane.

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

* **PWM Marketing Mistake**: We originally sold the Maple advertising
  22 channels of 16-bit hardware PWM; the correct number is 15.

Recommended Reading
-------------------

* STMicro documentation for STM32F103RB microcontroller:

    * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
    * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
    * `Programming Manual <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_ (assembly language and register reference)

.. rubric:: Footnotes

.. [#frev2_4] Revs 2 and 4 were prototypes that didn't pass internal
   testing.
