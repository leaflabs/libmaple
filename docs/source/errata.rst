.. _errata:

========
 Errata
========

This page is a collection of known issues and warnings for each
revision of the Maple board. The failure modes aren't design errors,
but are easy ways to break or damage your board permanently. For a
list of differences between the Maple and Arduinos, see the
:ref:`compatibility reference <compatibility>`.

.. contents:: Contents
   :local:

Maple Rev 5
-----------

These boards went on sale in November 2010.  They have white buttons,
and "r5" in small print near the "LeafLabs Maple" text next to the
"infinity-leaf" logo, among other changes:

.. figure:: /_static/img/maple_rev5.png
   :align: center
   :alt: Maple Rev 5

Known issues:

* **GPIO 39-43 not configured**: this is really more of a software
  "TODO" item.  Some of the JTAG header pins are numbered 39-43. These
  STM32 pins are indeed fully functional :ref:`GPIO <gpio>` when the a
  :ref:`JTAG <jtag>` device is not connected, but we have not enabled
  them in software and thus they can not be accessed with the regular
  :ref:`lang-pinmode` or :ref:`lang-digitalwrite` functions.

Potential failure modes:

* **TTL voltage on non-tolerant pins**: not all header pins are 5V
  compatible; connecting certain serial devices in the wrong way could
  over voltage the pins.  The :ref:`Pin-Mapping Mega Table
  <pin-mapping-mega-table>` details which pins are 5V-tolerant.

Maple Rev 3
-----------

This batch of boards went on sale beginning in May 2010. They have a
darker red silkscreen and the "infinity-leaf" logo:

.. figure:: /_static/img/maple_rev3.png
   :align: center
   :alt: Maple Rev 3

Known issues:

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
  methyl ether acetate (really?), and carbon dioxide.

* **Resistors on pins 0 and 1**: these header pins, which are RX/TX on
  USART2 (:ref:`Serial2 <lang-serial>`), have resistors in-line
  between the STM32 and the headers. These resistors increase the
  impedance of the lines for ADC reads and affect the open drain GPIO
  functionality of the pins.

  These resistors were accidentally copied over from older Arduino USB
  designs, where they appear to protect the USB-Serial converter from
  TTL voltage on the headers.

* **GPIO 39-43 not configured**: this is really more of a software
  "TODO" item.  Some of the JTAG header pins are numbered 39-43. These
  STM32 pins are indeed fully functional :ref:`GPIO <gpio>` when the a
  :ref:`JTAG <jtag>` device is not connected, but we have not enabled
  them in software and thus they can not be accessed with the regular
  :ref:`lang-pinmode` or :ref:`lang-digitalwrite` functions.

* **Silkscreen Errors**: the silkscreen on the bottom indicated PWM
  functionality on pin 25 and listen the external header GND pin as
  number 38 (actually 38 is connected to the BUT button). We manually
  sharpied over both of these mistakes.

* **PWM Marketing Mistake**: We originally sold the Maple advertising
  22 channels of 16-bit hardware PWM; actually the Maple only has 15.

Potential failure modes:

* **TTL voltage on non-tolerant pins**: not all header pins are 5V
  compatible; connecting certain serial devices in the wrong way could
  over voltage the pins.  The :ref:`Pin-Mapping Mega Table
  <pin-mapping-mega-table>` details which pins are 5V-tolerant.

Maple Rev 1
-----------

This batch of 100 boards shipped in later 2009. They have a red
silkscreen and the logo is a single pixelated leaf:

.. figure:: /_static/img/maple_rev1.png
   :align: center
   :alt: Maple Rev 1

Known issues:

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
  22 channels of 16-bit hardware PWM; actually the Maple only has 15.

Potential failure modes:

* **TTL voltage on non-tolerant pins**: not all header pins are 5v
  compatible; connecting certain serial devices in the wrong way could
  over voltage the pins. The :ref:`Pin-Mapping Mega Table
  <pin-mapping-mega-table>` details which pins are 5V-tolerant.
